#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
    glm::vec3 tmpV;
    glm::vec3 position;
    virtual glm::mat4 getViewMatrix() = 0;
    virtual glm::mat4 getProjectionMatrix() = 0;
    virtual glm::vec3 unproject(glm::vec3 &) = 0;
};

#endif // __CAMERA_H__