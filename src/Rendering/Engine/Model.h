#pragma once

#include <p6/p6.h>
#include <tiny_gltf.h>
#include <string>
#include "Rendering/Programs/Texture/Texture.h"

class Model {
public:
    explicit Model(std::string const& path, bool isBinaryGltf = false);

    void playAllAnimations(float currentTime);
    void draw() const;

    tinygltf::Model const& getModel() const { return _model; };

private:
    void loadModel(std::string const& path, bool isBinaryGltf);
    void bindModel();
    void bindModelNodes(tinygltf::Node&);
    void bindMesh(tinygltf::Mesh&);
    void bindAllPrimitiveAttributes(const tinygltf::Primitive& primitive);

    float computeInterpolationFactor(float currentTime, const tinygltf::AnimationSampler& sampler, const float* inputData, int keyframeIndex) const;
    void  updateNodeTransform(const tinygltf::AnimationChannel& channel, tinygltf::Node& node, const float* outputData, int keyframeIndex, float factor) const;

    static std::optional<const tinygltf::Texture*> getTexture(tinygltf::Model& model);

    void drawNode(tinygltf::Node const&) const;
    void drawMesh(tinygltf::Mesh const&) const;

    void createAndBindTexture(const tinygltf::Texture& texture);
    void createEachVbos();
    void cleanVbos();

private:
    tinygltf::Model    _model{};
    tinygltf::TinyGLTF _loader{};
    GLuint             _textureId{};

    GLuint                _vao{};
    std::map<int, GLuint> _vbos;
};