#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec4 fFragColor;

void main() {
    fFragColor = vec4(0., 1., 1., 0.3);
}