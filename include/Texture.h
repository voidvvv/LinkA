#ifndef __TEXTURE_H__
#define __TEXTURE_H__
#include "stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

class Texture
{
public:
    GLuint ID;
    int width, height, nrChannels;
    bool suc;
    Texture(const char* path);
    void bind(int i);
};

#endif // __TEXTURE_H__