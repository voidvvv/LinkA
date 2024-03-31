#ifndef __ORTHOGRAPHICCAMERA_H__
#define __ORTHOGRAPHICCAMERA_H__
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class OrthographicCamera
{
public:
    glm::vec3 worldUp;
    glm::vec3 up;
    glm::vec3 position;
    glm::vec3 direct;
    glm::vec3 right;

    glm::mat4 projection;

    OrthographicCamera(const float &width, const float &heigh);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    void update();
};

#endif // __ORTHOGRAPHICCAMERA_H__