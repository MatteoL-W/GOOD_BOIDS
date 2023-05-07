#pragma once

#include <p6/p6.h>
#include <tiny_gltf.h>
#include <string>
#include "Rendering/Programs/Texture/Texture.h"

class Model {
public:
    explicit Model(std::string const& path, bool isBinaryGltf = false);
    void animateNodes();
    void draw() const;

private:
    void loadModel(std::string const& path, bool isBinaryGltf);
    void bindModel();
    void bindModelNodes(tinygltf::Node&);
    void bindMesh(tinygltf::Mesh&);
    void bindAllPrimitiveAttributes(const tinygltf::Primitive& primitive);

    void                               loadAnimation();
    void                               processAnimation(const tinygltf::Animation& animation);
    std::optional<tinygltf::Animation> getAnimationForNode(int nodeId) const;

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