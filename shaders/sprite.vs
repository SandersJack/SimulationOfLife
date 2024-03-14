#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform vec2 shapePosition;
uniform mat4 model;

void main()
{
    TexCoords = 1.0 - vertex.zw;
    gl_Position = model * vec4(shapePosition + vertex.xy, 0.0, 1.0);
}