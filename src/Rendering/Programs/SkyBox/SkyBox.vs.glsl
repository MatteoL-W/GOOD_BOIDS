#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 vTexCoords;

uniform mat4 uMVPMatrix;

void main()
{
    vTexCoords = vec3(aPos.x, 1-aPos.y, aPos.z);
    vec4 pos = uMVPMatrix * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}