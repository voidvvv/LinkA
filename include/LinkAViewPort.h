#ifndef __LINKAVIEWPORT_H__
#define __LINKAVIEWPORT_H__
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class LinKAViewPort
{
public:
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
    void apply();
    void apply(GLint, GLint,GLsizei,GLsizei);
    glm::vec4 getV4(); 
};

#endif // __LINKAVIEWPORT_H__