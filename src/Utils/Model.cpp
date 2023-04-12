#include "Model.h"
#include <stdexcept>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

Model::Model(std::string path)
{
    loadModel(path);
    bindModel();
}
void Model::loadModel(std::string path)
{
    std::string err;
    std::string warn;

    bool ret = _loader.LoadASCIIFromFile(&_model, &err, &warn, path.c_str());
    // bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, argv[1]); // for binary glTF(.glb)

    if (!warn.empty())
        throw std::runtime_error(warn.c_str());

    if (!err.empty())
        throw std::runtime_error(err.c_str());

    if (!ret)
        throw std::runtime_error("Failed to parse gltf");
    // https://gltf-viewer-tutorial.gitlab.io/initialization/
    //  Assume the model is loaded and stored in a variable named `model`
}

void Model::bindModel()
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    const tinygltf::Scene& scene = _model.scenes[_model.defaultScene];
    for (size_t i = 0; i < scene.nodes.size(); ++i)
    {
        // assert((scene.nodes[i] >= 0) && (scene.nodes[i] < _model.nodes.size()));
        bindModelNodes(_model.nodes[scene.nodes[i]]);
    }

    glBindVertexArray(0);

    for (auto it = _vbos.cbegin(); it != _vbos.cend();) {
        tinygltf::BufferView bufferView = _model.bufferViews[it->first];
        if (bufferView.target != GL_ELEMENT_ARRAY_BUFFER) {
            glDeleteBuffers(1, &_vbos[it->first]);
            _vbos.erase(it++);
        }
        else {
            ++it;
        }
    }

    _vaoAndEbos = {_vao, _vbos};
}

void Model::bindModelNodes(tinygltf::Node& node)
{
    if ((node.mesh >= 0) && (node.mesh < _model.meshes.size()))
    {
        bindMesh(_model.meshes[node.mesh]);
    }

    for (size_t i = 0; i < node.children.size(); i++)
    {
        // assert((node.children[i] >= 0) && (node.children[i] < model.nodes.size()));
        bindModelNodes(_model.nodes[node.children[i]]);
    }
}

void Model::bindMesh(tinygltf::Mesh& mesh)
{
    for (size_t i = 0; i < _model.bufferViews.size(); ++i)
    {
        const tinygltf::BufferView& bufferView = _model.bufferViews[i];
        if (bufferView.target == 0)
        { // TODO impl drawarrays
            std::cout << "WARN: bufferView.target is zero" << std::endl;
            continue;
        }

        const tinygltf::Buffer& buffer = _model.buffers[bufferView.buffer];
        std::cout << "bufferview.target " << bufferView.target << std::endl;

        GLuint vbo;
        glGenBuffers(1, &vbo);
        _vbos[i] = vbo;
        glBindBuffer(bufferView.target, vbo);

        std::cout << "buffer.data.size = " << buffer.data.size()
                  << ", bufferview.byteOffset = " << bufferView.byteOffset
                  << std::endl;

        glBufferData(bufferView.target, bufferView.byteLength, &buffer.data.at(0) + bufferView.byteOffset, GL_STATIC_DRAW);
    }

    for (size_t i = 0; i < mesh.primitives.size(); ++i)
    {
        tinygltf::Primitive primitive = mesh.primitives[i];
        if (primitive.indices < 0)
            continue;

        tinygltf::Accessor indexAccessor = _model.accessors[primitive.indices];

        for (auto& attrib : primitive.attributes)
        {
            tinygltf::Accessor accessor   = _model.accessors[attrib.second];
            int                byteStride = accessor.ByteStride(_model.bufferViews[accessor.bufferView]);
            glBindBuffer(GL_ARRAY_BUFFER, _vbos[accessor.bufferView]);

            int size = 1;
            if (accessor.type != TINYGLTF_TYPE_SCALAR)
                size = accessor.type;

            int vaa = -1;
            if (attrib.first.compare("POSITION") == 0)
                vaa = 0;
            if (attrib.first.compare("NORMAL") == 0)
                vaa = 1;
            if (attrib.first.compare("TEXCOORD_0") == 0)
                vaa = 2;
            if (vaa > -1)
            {
                glEnableVertexAttribArray(vaa);
                glVertexAttribPointer(vaa, size, accessor.componentType, accessor.normalized ? GL_TRUE : GL_FALSE, byteStride, BUFFER_OFFSET(accessor.byteOffset));
            }
            else
                std::cout << "vaa missing: " << attrib.first << std::endl;
        }

        if (_model.textures.size() > 0)
        {
            // fixme: Use material's baseColor
            tinygltf::Texture& tex = _model.textures[0];

            if (tex.source > -1)
            {
                GLuint texid;
                glGenTextures(1, &texid);

                tinygltf::Image& image = _model.images[tex.source];

                glBindTexture(GL_TEXTURE_2D, texid);
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

                GLenum format = GL_RGBA;

                if (image.component == 1)
                {
                    format = GL_RED;
                }
                else if (image.component == 2)
                {
                    format = GL_RG;
                }
                else if (image.component == 3)
                {
                    format = GL_RGB;
                }
                else
                {
                    // ???
                }

                GLenum type = GL_UNSIGNED_BYTE;
                if (image.bits == 8)
                {
                    // ok
                }
                else if (image.bits == 16)
                {
                    type = GL_UNSIGNED_SHORT;
                }
                else
                {
                    // ???
                }

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, format, type, &image.image.at(0));
            }
        }
    }
}
void Model::draw()
{
    glBindVertexArray(_vaoAndEbos.first);

    const tinygltf::Scene &scene = _model.scenes[_model.defaultScene];
    for (size_t i = 0; i < scene.nodes.size(); ++i) {
        drawNode(_model.nodes[scene.nodes[i]]);
    }

    glBindVertexArray(0);
}
void Model::drawNode(tinygltf::Node& node)
{
    if ((node.mesh >= 0) && (node.mesh < _model.meshes.size())) {
        drawMesh(_model.meshes[node.mesh]);
    }
    for (size_t i = 0; i < node.children.size(); i++) {
        drawNode(_model.nodes[node.children[i]]);
    }
}

void Model::drawMesh(tinygltf::Mesh& mesh)
{
    for (size_t i = 0; i < mesh.primitives.size(); ++i) {
        tinygltf::Primitive primitive = mesh.primitives[i];

        if (primitive.indices < 0)
            continue;

        tinygltf::Accessor indexAccessor = _model.accessors[primitive.indices];

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbos.at(indexAccessor.bufferView));

        glDrawElements(primitive.mode, indexAccessor.count,
                       indexAccessor.componentType,
                       BUFFER_OFFSET(indexAccessor.byteOffset));
    }
}
