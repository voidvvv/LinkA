#version 330 core
layout (location = 0) in vec4 aPos;

out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main () {
    gl_Position =projection *  view *  model * vec4(aPos.xy,0.f,1.0f);

    TexCoord = aPos.zw;
}