#include "Model.h"
#include <stdexcept>

template<typename T>
inline constexpr T* bufferOffset(std::size_t offset)
{
    return reinterpret_cast<T*>(static_cast<std::uintptr_t>(offset));
}

Model::Model(std::string const& path, bool const isBinaryGltf)
{
    loadModel(path, isBinaryGltf);
    bindModel();
}

void Model::loadModel(std::string const& path, bool const isBinaryGltf)
{
    std::string err;
    std::string warn;

    bool const hasLoaded = isBinaryGltf ? _loader.LoadBinaryFromFile(&_model, &err, &warn, path)
                                        : _loader.LoadASCIIFromFile(&_model, &err, &warn, path);

    if (!warn.empty() || !err.empty())
        throw std::runtime_error((warn.empty() ? warn.c_str() : err.c_str()));

    if (!hasLoaded)
        throw std::runtime_error("Failed to parse gltf");
}

void Model::bindModel()
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    auto const& scene = _model.scenes[_model.defaultScene];
    for (int const node : scene.nodes)
        // assert((node >= 0) && (node < _model.nodes.size()));
        bindModelNodes(_model.nodes[node]);

    glBindVertexArray(0);

    cleanVbos();
}

void Model::cleanVbos()
{
    for (auto it = _vbos.begin(); it != _vbos.end();)
    {
        auto const& [bufferViewId, vboId] = *it;
        auto const& bufferView            = _model.bufferViews[bufferViewId];

        if (bufferView.target != GL_ELEMENT_ARRAY_BUFFER)
        {
            glDeleteBuffers(1, &vboId);
            it = _vbos.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Model::bindModelNodes(tinygltf::Node& node)
{
    if ((node.mesh >= 0) && (node.mesh < static_cast<int>(_model.meshes.size())))
        bindMesh(_model.meshes[node.mesh]);

    for (int const child : node.children)
        // assert((node.children[i] >= 0) && (node.children[i] < _model.nodes.size()));
        bindModelNodes(_model.nodes[child]);
}

void Model::bindMesh(tinygltf::Mesh& mesh)
{
    createEachVbos();

    for (auto const& primitive : mesh.primitives)
    {
        bindAllPrimitiveAttributes(primitive);

        auto const texture = getTexture(_model);
        if (texture.has_value())
            createAndBindTexture(*texture.value());
    }
}

std::optional<const tinygltf::Texture*> Model::getTexture(tinygltf::Model& model)
{
    if (model.textures.empty())
        return std::nullopt;

    tinygltf::Texture const& texture = model.textures[0];

    if (texture.source < 0)
        return std::nullopt;

    return &texture;
}

void Model::createAndBindTexture(const tinygltf::Texture& texture)
{
    glGenTextures(1, &_textureId);

    auto& image = _model.images[texture.source];

    glBindTexture(GL_TEXTURE_2D, _textureId);
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

void Model::bindAllPrimitiveAttributes(const tinygltf::Primitive& primitive)
{
    for (auto const& attrib : primitive.attributes)
    {
        auto const accessor   = _model.accessors[attrib.second];
        int const  byteStride = accessor.ByteStride(_model.bufferViews[accessor.bufferView]);
        glBindBuffer(GL_ARRAY_BUFFER, _vbos[accessor.bufferView]);

        int size = 1;
        if (accessor.type != TINYGLTF_TYPE_SCALAR)
            size = accessor.type;

        std::optional<int> vaa = std::nullopt;
        if (attrib.first == "POSITION")
            vaa = 0;
        if (attrib.first == "NORMAL")
            vaa = 1;
        if (attrib.first == "TEXCOORD_0")
            vaa = 2;

        if (vaa.has_value())
        {
            glEnableVertexAttribArray(vaa.value());
            glVertexAttribPointer(vaa.value(), size, accessor.componentType, accessor.normalized ? GL_TRUE : GL_FALSE, byteStride, bufferOffset<char>(accessor.byteOffset));
        }
    }
}

void Model::createEachVbos()
{
    for (size_t i = 0; i < _model.bufferViews.size(); ++i)
    {
        auto const& bufferView = _model.bufferViews[i];
        if (bufferView.target == 0)
            // Unsupported bufferView from TinyGLTF;
            continue;

        auto const& buffer = _model.buffers[bufferView.buffer];

        GLuint vbo = 0;
        glGenBuffers(1, &vbo);
        _vbos[static_cast<int>(i)] = vbo;

        glBindBuffer(bufferView.target, vbo);
        glBufferData(bufferView.target, static_cast<GLsizeiptr>(bufferView.byteLength), std::next(std::data(buffer.data), static_cast<int>(bufferView.byteOffset)), GL_STATIC_DRAW);
    }
}

void Model::draw() const
{
    glBindVertexArray(_vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    auto const& scene = _model.scenes[_model.defaultScene];
    for (int const node : scene.nodes)
        drawNode(_model.nodes[node]);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void Model::drawNode(tinygltf::Node const& node) const
{
    if ((node.mesh >= 0) && (node.mesh < static_cast<int>(_model.meshes.size())))
        drawMesh(_model.meshes[node.mesh]);

    for (int const i : node.children)
        drawNode(_model.nodes[i]);
}

void Model::drawMesh(tinygltf::Mesh const& mesh) const
{
    for (const auto& primitive : mesh.primitives)
    {
        auto const indexAccessor = _model.accessors[primitive.indices];
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbos.at(indexAccessor.bufferView));
        glDrawElements(primitive.mode, static_cast<GLsizei>(indexAccessor.count), indexAccessor.componentType, bufferOffset<char>(indexAccessor.byteOffset));
    }
}

void Model::playAllAnimations(float currentTime)
{
    for (tinygltf::Animation const& animation : _model.animations)
        for (tinygltf::AnimationChannel const& channel : animation.channels)
        {
            auto&       node    = _model.nodes[channel.target_node];
            auto const& sampler = animation.samplers[channel.sampler];

            auto const& inputAccessor  = _model.accessors[sampler.input];
            auto const& outputAccessor = _model.accessors[sampler.output];

            auto const& inputBufferView  = _model.bufferViews[inputAccessor.bufferView];
            auto const& outputBufferView = _model.bufferViews[outputAccessor.bufferView];

            auto const& inputBuffer  = _model.buffers[inputBufferView.buffer];
            auto const& outputBuffer = _model.buffers[outputBufferView.buffer];

            // Calculate the input and output data pointers
            auto const* inputData  = reinterpret_cast<const float*>(&inputBuffer.data[inputBufferView.byteOffset + inputAccessor.byteOffset]);
            auto const* outputData = reinterpret_cast<const float*>(&outputBuffer.data[outputBufferView.byteOffset + outputAccessor.byteOffset]);

            // Find the appropriate keyframe index for the current time
            size_t keyframeIndex = 0;
            while (keyframeIndex < inputAccessor.count - 1 && currentTime > inputData[keyframeIndex + 1])
                keyframeIndex++;

            float factor = computeInterpolationFactor(currentTime, sampler, inputData, keyframeIndex);
            updateNodeTransform(channel, node, outputData, keyframeIndex, factor);
        }
}

float Model::computeInterpolationFactor(float currentTime, const tinygltf::AnimationSampler& sampler, const float* inputData, int keyframeIndex) const
{
    float factor = 0.f;
    if (sampler.interpolation == "LINEAR")
    {
        float const deltaTime = inputData[keyframeIndex + 1] - inputData[keyframeIndex];
        if (deltaTime > 0.0f)
            factor = (currentTime - inputData[keyframeIndex]) / deltaTime;
    }
    return factor;
}

void Model::updateNodeTransform(const tinygltf::AnimationChannel& channel, tinygltf::Node& node, const float* outputData, int keyframeIndex, float factor) const
{
    if (channel.target_path == "translation")
    {
        float const* startValue = outputData + keyframeIndex * 3;
        float const* endValue   = outputData + (keyframeIndex + 1) * 3;
        node.translation.resize(3);
        for (int i = 0; i < 3; ++i)
            node.translation[i] = static_cast<double>(startValue[i] + factor * (endValue[i] - startValue[i]));
    }

    else if (channel.target_path == "rotation")
    {
        const float* startValue = outputData + keyframeIndex * 4;
        const float* endValue   = outputData + (keyframeIndex + 1) * 4;
        glm::quat    startQuaternion(startValue[0], startValue[1], startValue[2], startValue[3]);
        glm::quat    endQuaternion(endValue[0], endValue[1], endValue[2], endValue[3]);
        glm::quat    resultQuaternion = glm::slerp(startQuaternion, endQuaternion, factor);
        glm::normalize(resultQuaternion);
        node.rotation.resize(4);
        node.rotation[0] = resultQuaternion[0];
        node.rotation[1] = resultQuaternion[1];
        node.rotation[2] = resultQuaternion[2];
        node.rotation[3] = resultQuaternion[3];
    }

    else if (channel.target_path == "scale")
    {
        const float* startValue = outputData + keyframeIndex * 3;
        const float* endValue   = outputData + (keyframeIndex + 1) * 3;

        node.scale.resize(3);
        for (int i = 0; i < 3; ++i)
        {
            node.scale[i] = static_cast<double>(startValue[i] + factor * (endValue[i] - startValue[i]));
        }

    }

    else
        std::cerr << "Unsupported animation target path: " << channel.target_path << std::endl;
}