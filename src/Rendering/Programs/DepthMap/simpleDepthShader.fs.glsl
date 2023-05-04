#version 330 core

void main()
{
    // This line is optional
    gl_FragDepth = gl_FragCoord.z;
}