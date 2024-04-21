#ifndef __PERSPECTCAMERA_H__
#define __PERSPECTCAMERA_H__
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../include/Camera.h"
static const float YAW = 90.0f;
static const float PITCH = 0.0f;
static const float ZOOM = 45.0f;
class PerspectCamera : public Camera
{
public:
    // euler Angles



    bool constrainPitch;

    PerspectCamera();
    virtual glm::mat4 getViewMatrix();
    virtual glm::mat4 getProjectionMatrix();
    virtual glm::vec3 unproject(glm::vec3 &, glm::vec4);
    virtual glm::vec3 unproject(glm::vec3 &);

    virtual glm::vec3 project(glm::vec3 &);
    virtual glm::vec3 project(glm::vec3 &, glm::vec4);
    virtual void update();
};

#endif // __PERSPECTCAMERA_H__