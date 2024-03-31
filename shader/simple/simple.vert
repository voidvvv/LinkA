#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 a_texCoord;


out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main () {
    gl_Position =projection *  view *  model * vec4(aPos,0.f,1.0f);

    TexCoord = a_texCoord;
}