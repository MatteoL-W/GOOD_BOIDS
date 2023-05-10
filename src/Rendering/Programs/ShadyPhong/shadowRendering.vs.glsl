#version 330 core
layout (location = 0) in vec3 aVertexPosition;
layout (location = 1) in vec3 aVertexNormal;
layout (location = 2) in vec2 aVertexTexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;
uniform mat4 uLightSpaceMatrix;

void main()
{
    vs_out.FragPos           = vec3(uModel * vec4(aVertexPosition, 1.0));
    vs_out.Normal            = transpose(inverse(mat3(uModel))) * aVertexNormal;
    vs_out.TexCoords         = vec2(aVertexTexCoords.x, 1-aVertexTexCoords.y);// Inverse UV to have right texture (still don't know why)
    vs_out.FragPosLightSpace = uLightSpaceMatrix * vec4(vs_out.FragPos, 1.0);

    gl_Position              = uProjection * uView * vec4(vs_out.FragPos, 1.0);
}