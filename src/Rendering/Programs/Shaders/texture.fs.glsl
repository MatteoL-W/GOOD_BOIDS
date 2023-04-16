#version 330 core

uniform sampler2D uTexture;

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec4 fFragColor;

void main() {
    fFragColor = texture(uTexture, vTexCoords);
}