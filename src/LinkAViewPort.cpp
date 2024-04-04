#include "LinkAViewPort.h"
#include <iostream>

extern GLFWwindow* window;

void LinKAViewPort::apply()
{
    x = 0;
    y = 0;
    glfwGetWindowSize(window,&width,&height);
        // std::cout << "apply - viewport: x : " << x << " - y: " << y << " - width: " << width << " - height: " << height << std::endl;

    glViewport(x,y,width,height);
}

void LinKAViewPort::apply(GLint x, GLint y,GLsizei w,GLsizei h)
{
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
    glViewport(x,y,width,height);
}

glm::vec4 LinKAViewPort::getV4()
{
    // std::cout << "viewport: x : " << x << " - y: " << y << " - width: " << width << " - height: " << height << std::endl;
    return glm::vec4(x,y,width,height);
}
