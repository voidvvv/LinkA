#include "OrthographicCamera.h"
#include "LinkAViewPort.h"
#include <iostream>

extern LinKAViewPort *linKA_viewport;
;
OrthographicCamera::OrthographicCamera(const float &width, const float &heigh) : worldUp(0, 1, 0), direct(0, 0, -1), up(0, 1, 0)
{
    projection = glm::ortho(0.0f, width, 0.0f, heigh, -1.0f, 1.0f);
    this->position = glm::vec3(0, 0, 0);
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

glm::vec3 OrthographicCamera::unproject(glm::vec3 &screenPos)
{
    std::cout << "screen pos: x: " << screenPos.x << " = y: " << screenPos.y << "  = z: " << screenPos.z << std::endl;

    this->tmpV = glm::unProject(screenPos, getViewMatrix(), getProjectionMatrix(), linKA_viewport->getV4());
    std::cout << "worldPos : x: " << tmpV.x << " = y: " << tmpV.y << std::endl;

    return tmpV;
}

void OrthographicCamera::update()
{
    // todo
}
