#include "Model.h"
#include <stdexcept>
#include "Camera/CameraManager.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/type_ptr.hpp"

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

Model::Model(const std::string& path)
{
    loadModel(path);
    bindModel();
}

void Model::loadModel(const std::string& path)
{
    std::string err;
    std::string warn;

    bool const ret = _loader.LoadASCIIFromFile(&_model, &err, &warn, path);
    // bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, argv[1]); // for binary glTF(.glb)

    if (!warn.empty())
        throw std::runtime_error(warn.c_str());

    if (!err.empty())
        throw std::runtime_error(err.c_str());

    if (!ret)
        throw std::runtime_error("Failed to parse gltf");
}

void Model::bindModel()
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    const tinygltf::Scene& scene = _model.scenes[_model.defaultScene];
    for (int const node : scene.nodes)
        // assert((node >= 0) && (node < _model.nodes.size()));
        bindModelNodes(_model.nodes[node]);

    glBindVertexArray(0);

    cleanVbos();

    _vaoAndEbos = {_vao, _vbos};
}

void Model::cleanVbos()
{
    for (auto it = _vbos.cbegin(); it != _vbos.cend();)
    {
        tinygltf::BufferView const bufferView = _model.bufferViews[it->first];
        if (bufferView.target != GL_ELEMENT_ARRAY_BUFFER)
        {
            glDeleteBuffers(1, &_vbos[it->first]);
            _vbos.erase(it++);
        }
        else
            ++it;
    }
}

void Model::bindModelNodes(tinygltf::Node& node)
{
    if ((node.mesh >= 0) && (node.mesh < static_cast<int>(_model.meshes.size())))
        bindMesh(_model.meshes[node.mesh]);

    for (int const i : node.children)
        // assert((node.children[i] >= 0) && (node.children[i] < _model.nodes.size()));
        bindModelNodes(_model.nodes[i]);
}

void Model::bindMesh(tinygltf::Mesh& mesh)
{
    for (size_t i = 0; i < _model.bufferViews.size(); ++i)
    {
        const tinygltf::BufferView& bufferView = _model.bufferViews[i];
        if (bufferView.target == 0)
            continue;

        const tinygltf::Buffer& buffer = _model.buffers[bufferView.buffer];
        std::cout << "bufferview.target " << bufferView.target << std::endl;

        GLuint vbo = 0;
        glGenBuffers(1, &vbo);
        _vbos[i] = vbo;

        glBindBuffer(bufferView.target, vbo);
        glBufferData(bufferView.target, bufferView.byteLength, &buffer.data.at(0) + bufferView.byteOffset, GL_STATIC_DRAW);
    }

    for (auto const& primitive : mesh.primitives)
    {
        tinygltf::Accessor const indexAccessor = _model.accessors[primitive.indices];

        for (auto const& attrib : primitive.attributes)
        {
            tinygltf::Accessor const accessor   = _model.accessors[attrib.second];
            int const                byteStride = accessor.ByteStride(_model.bufferViews[accessor.bufferView]);
            glBindBuffer(GL_ARRAY_BUFFER, _vbos[accessor.bufferView]);

            int size = 1;
            if (accessor.type != TINYGLTF_TYPE_SCALAR)
                size = accessor.type;

            std::optional<int> vaa{};
            if (attrib.first == "POSITION")
                vaa = 0;
            if (attrib.first == "NORMAL")
                vaa = 1;
            if (attrib.first == "TEXCOORD_0")
                vaa = 2;

            if (vaa.has_value())
            {
                glEnableVertexAttribArray(vaa.value());
                glVertexAttribPointer(vaa.value(), size, accessor.componentType, accessor.normalized ? GL_TRUE : GL_FALSE, byteStride, BUFFER_OFFSET(accessor.byteOffset));
            }
        }

        if (_model.textures.empty())
            continue;

        // fixme: Use material's baseColor
        tinygltf::Texture const& tex = _model.textures[0];

        if (tex.source < 0)
            continue;

        GLuint textureId{};
        glGenTextures(1, &textureId);

        tinygltf::Image& image = _model.images[tex.source];

        glBindTexture(GL_TEXTURE_2D, textureId);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        GLenum format = GL_RGBA;

        if (image.component == 1)
            format = GL_RED;
        else if (image.component == 2)
            format = GL_RG;
        else if (image.component == 3)
            format = GL_RGB;

        GLenum type = GL_UNSIGNED_BYTE;
        if (image.bits == 16)
            type = GL_UNSIGNED_SHORT;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, format, type, &image.image.at(0));
    }
}

void Model::draw(p6::Context& ctx)
{
    _shader._program.use();

    auto cameraManager    = Camera::getCameraInstance();
    auto modelViewMatrix  = cameraManager.getViewMatrix() * glm::scale(glm::mat4(1), glm::vec3(0.10f));
    auto projectionMatrix = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), .1f, 100.f);
    auto normalMatrix     = glm::transpose(glm::inverse(modelViewMatrix));

    glUniformMatrix4fv(_shader.uMVMatrix, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
    glUniformMatrix4fv(_shader.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix * modelViewMatrix));
    glUniformMatrix4fv(_shader.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

    glBindVertexArray(_vaoAndEbos.first);

    const tinygltf::Scene& scene = _model.scenes[_model.defaultScene];
    for (int const node : scene.nodes)
        drawNode(_model.nodes[node]);

    glBindVertexArray(0);
}

void Model::drawNode(tinygltf::Node& node)
{
    if ((node.mesh >= 0) && (node.mesh < static_cast<int>(_model.meshes.size())))
        drawMesh(_model.meshes[node.mesh]);

    for (int const i : node.children)
        drawNode(_model.nodes[i]);
}

void Model::drawMesh(tinygltf::Mesh& mesh)
{
    for (const auto& primitive : mesh.primitives)
    {
        tinygltf::Accessor const indexAccessor = _model.accessors[primitive.indices];
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbos.at(indexAccessor.bufferView));
        glDrawElements(primitive.mode, indexAccessor.count, indexAccessor.componentType, BUFFER_OFFSET(indexAccessor.byteOffset));
    }
}
