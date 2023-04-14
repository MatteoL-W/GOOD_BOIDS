#pragma once

#include <p6/p6.h>
#include "Program/Texture.h"
#include "string"
#include "tiny_gltf.h"

class Model {
public:
    Model(std::string const& path, bool isBinaryGltf = false);
    void draw(p6::Context& ctx);

private:
    void loadModel(std::string const& path, bool isBinaryGltf);
    void bindModel();
    void bindModelNodes(tinygltf::Node&);
    void bindMesh(tinygltf::Mesh&);

    std::optional<const tinygltf::Texture*> getTexture(tinygltf::Model& model);

    void drawNode(tinygltf::Node&);
    void drawMesh(tinygltf::Mesh&);

    void createEachVbos();
    void cleanVbos();

private:
    tinygltf::Model    _model{};
    tinygltf::TinyGLTF _loader{};
    Program::Texture   _shader{};

    GLuint                _vao{};
    std::map<int, GLuint> _vbos;

    std::pair<GLuint, std::map<int, GLuint>> _vaoAndEbos{};
    void                                     bindAllPrimitiveAttributes(const tinygltf::Primitive& primitive);
    void                                     createAndBindTexture(const tinygltf::Texture& texture);
};