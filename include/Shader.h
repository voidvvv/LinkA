#ifndef __SHADER_H__
#define __SHADER_H__
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class ShaderProgram
{
public:
    GLuint ID = 0;
    ShaderProgram(const char *vertPath, const char *fragpath);
    ShaderProgram(const char *vertSource, const char *fragSource, int);
    void use();

    void setUniformMat4(const char *name, glm::mat4);
    void setUniformMat3(const char *name, glm::mat3);

    void setUniformInt(const char *name, int);
    void setUniformFloat(const char *name, float);
    void setUniformFloat3(const char *name, float *);
    void setUniformFloat3(const char *name, float, float, float);

private:
    void parseToProgram(const char *vertSource, const char *fragSource);
};

#endif // __SHADER_H__