#version 330 core
uniform sampler2D texture0;
uniform vec3 u_color;

in vec2 TexCoords;

out vec4 FragColor;
void main(){
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(texture0, TexCoords).r);
    FragColor = vec4(u_color,1.f) * sampled;
}