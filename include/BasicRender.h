#ifndef __BASICRENDER_H__
#define __BASICRENDER_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

#include "Shader.h"



// render use for rendering basic shape, include line, dot and rectangle
class BasicRender
{
private:
    float vertex[5000];
    int vIndex;
    int vSize;
    GLuint VAO;
    GLuint VBO;
    ShaderProgram *shader; 
    void setVec3(glm::vec3);
    unsigned int vertexCount;

public:
    BasicRender(ShaderProgram *shader);

    void initialData();

    void drawLine(glm::vec3 start,glm::vec3 end, Camera* camera , glm::vec3 color1 = glm::vec3(1.f), glm::vec3 color2 = glm::vec3(1.f));
    void drawLine(glm::vec2 start,glm::vec2 end, Camera* camera , glm::vec3 color1 = glm::vec3(1.f), glm::vec3 color2 = glm::vec3(1.f));

    // void drawFillLine();
};

#endif // __BASICRENDER_H__