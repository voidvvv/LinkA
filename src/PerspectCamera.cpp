#include "../include/PerspectCamera.h"

PerspectCamera::PerspectCamera()
{
    this->worldUp = glm::vec3(0, 1, 0);
    position = glm::vec3(0, 0, 0);
    constrainPitch = true;
    Yaw = YAW;
    Pitch = PITCH;
    Zoom = ZOOM;
    update();
}

glm::mat4 PerspectCamera::getViewMatrix()
{
    return this->viewMatrix;
}

glm::mat4 PerspectCamera::getProjectionMatrix()
{
    return this->projectionMatrix;
}

glm::vec3 PerspectCamera::unproject(glm::vec3 & screenPos, glm::vec4 viewPort)
{
    // empty
    this->tmpV = glm::unProject(screenPos, getViewMatrix(), getProjectionMatrix(), viewPort);

    return this->tmpV;
}

glm::vec3 PerspectCamera::unproject(glm::vec3 &screenPos)
{
    glm::vec4 viewPortTmp(0);
    GLFWwindow* window = camera_context::window;
    int width,height;
    glfwGetWindowSize(window, &width, &height);
    viewPortTmp[2] = width;
    viewPortTmp[3] = height;
    this->unproject(screenPos, viewPortTmp);
    return tmpV;
}

glm::vec3 PerspectCamera::project(glm::vec3 &, glm::vec4)
{
    // empty
    return glm::vec3();
}

glm::vec3 PerspectCamera::project(glm::vec3 &)
{
    // empty
    return glm::vec3();
}

void PerspectCamera::update()
{

    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    int width, height;
    GLFWwindow* window  = camera_context::window;
    glfwGetWindowSize(window, &width, &height);

    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    direct = glm::normalize(front);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(direct, worldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, front));

    projectionMatrix = glm::perspective(glm::radians(Zoom), (float)width / (float)height, 0.1f, 100.f);
    this->viewMatrix = glm::lookAt(position, position + direct, up);
}
