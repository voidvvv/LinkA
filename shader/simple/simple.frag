#version 330 core
uniform sampler2D texture0;
uniform vec3 u_color;

in vec2 TexCoord;

out vec4 FragColor;
void main(){
    FragColor = vec4(u_color,1.f) * texture2D(texture0,TexCoord);
}