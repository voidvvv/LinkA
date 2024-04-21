#include "../include/OrthographicCamera.h"
#include <iostream>

OrthographicCamera::OrthographicCamera(const float &width, const float &heigh)
{
    projectionMatrix = glm::ortho(0.0f, width, 0.0f, heigh, -1.0f, 1.0f);
    this->position = glm::vec3(0, 0, 0);
    worldUp = glm::vec3(0, 1, 0);
    direct = glm::vec3(0, 0, -1);
    up = glm::vec3(0, 1, 0);
    right = glm::vec3(1,0,0);
    // projection = glm::perspective(glm::radians(45.0f), (float)width/(float)heigh, 0.1f, 100.0f);
}

glm::mat4 OrthographicCamera::getViewMatrix()
{
    return glm::lookAt(position, position + direct, up);
}

glm::mat4 OrthographicCamera::getProjectionMatrix()
{
    return projectionMatrix;
}

glm::vec3 OrthographicCamera::unproject(glm::vec3 &screenPos, glm::vec4 viewPort)
{
    this->tmpV = glm::unProject(screenPos, getViewMatrix(), getProjectionMatrix(), viewPort);

    return this->tmpV;
}

glm::vec3 OrthographicCamera::unproject(glm::vec3 &screenPos)
{
    glm::vec4 viewPortTmp(0);
    GLFWwindow* window = camera_context::window;
    int width,height;
    glfwGetWindowSize(window, &width, &height);
    viewPortTmp[2] = width;
    viewPortTmp[3] = height;
    std::cout << viewPortTmp[0] << " - " << viewPortTmp[1] << " - " <<viewPortTmp[2] << " - " <<viewPortTmp[3] << " - " <<std::endl;
    this->unproject(screenPos, viewPortTmp);
    return tmpV;
}

glm::vec3 OrthographicCamera::project(glm::vec3 &)
{
    return glm::vec3();
}

glm::vec3 OrthographicCamera::project(glm::vec3 &, glm::vec4)
{
    return glm::vec3();
}

void OrthographicCamera::update()
{
    // todo
}
