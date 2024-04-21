#ifndef __CAMERA_H__
#define __CAMERA_H__
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace camera_context {
    extern GLFWwindow* window;
}

class Camera
{
public:
    float Yaw;
    float Pitch;
    float Zoom;
    glm::vec3 worldUp;
    glm::vec3 up;


    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    glm::vec3 direct;
    glm::vec3 right;

    glm::vec3 tmpV;
    glm::vec3 position;
    virtual glm::mat4 getViewMatrix() = 0;
    virtual glm::mat4 getProjectionMatrix() = 0;
    virtual glm::vec3 unproject(glm::vec3 &, glm::vec4) = 0;
    virtual glm::vec3 unproject(glm::vec3 &) = 0;

    virtual glm::vec3 project(glm::vec3 &) = 0;
    virtual glm::vec3 project(glm::vec3 &, glm::vec4) = 0;
    virtual void update() = 0;
};

#endif // __CAMERA_H__