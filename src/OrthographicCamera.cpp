#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(const float &width, const float &heigh) : worldUp(0, 1, 0), position(0, 0, 0), direct(0, 0, -1), up(0, 1, 0)
{
    projection = glm::ortho(0.0f, width, 0.0f, heigh, -1.0f, 1.0f);
    // projection = glm::perspective(glm::radians(45.0f), (float)width/(float)heigh, 0.1f, 100.0f);
}

glm::mat4 OrthographicCamera::getViewMatrix()
{
    return glm::lookAt(position, position + direct, up);
}

glm::mat4 OrthographicCamera::getProjectionMatrix()
{
    return projection;
}

void OrthographicCamera::update()
{
    // todo
}
