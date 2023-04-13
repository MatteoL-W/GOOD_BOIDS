#pragma once

#include <p6/p6.h>
#include "Program/Normal.h"
#include "string"
#include "tiny_gltf.h"

class Model {
public:
    Model(const std::string& path);
    void draw(p6::Context& ctx);

private:
    void loadModel(const std::string& path);
    void bindModel();
    void bindModelNodes(tinygltf::Node& node);
    void bindMesh(tinygltf::Mesh& mesh);

    void drawNode(tinygltf::Node& node);
    void drawMesh(tinygltf::Mesh& mesh);

private:
    tinygltf::Model    _model{};
    tinygltf::TinyGLTF _loader{};
    Program::Normal    _shader{};

    GLuint                _vao{};
    std::map<int, GLuint> _vbos;

    std::pair<GLuint, std::map<int, GLuint>> _vaoAndEbos{};
};