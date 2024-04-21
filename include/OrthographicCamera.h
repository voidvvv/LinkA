#ifndef __ORTHOGRAPHICCAMERA_H__
#define __ORTHOGRAPHICCAMERA_H__

#include "Camera.h"

class OrthographicCamera : public Camera
{
public:
    OrthographicCamera(const float &width, const float &heigh);

    glm::mat4 getViewMatrix() override;
    glm::mat4 getProjectionMatrix() override;
    virtual glm::vec3 unproject(glm::vec3 &, glm::vec4);
    virtual glm::vec3 unproject(glm::vec3 &) ;

    virtual glm::vec3 project(glm::vec3 &);
    virtual glm::vec3 project(glm::vec3 &, glm::vec4);

    virtual void update();
};

#endif // __ORTHOGRAPHICCAMERA_H__