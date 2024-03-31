#ifndef __MAINSCREEN_H__
#define __MAINSCREEN_H__
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Screen.h"
#include "Texture.h"
#include "OrthographicCamera.h"
#include "TextApplication.h"

class MainScreen : public Screen
{
private:
    Texture* face;
    // test
    GLuint VAO,VBO;

    float* vertex;
    GLuint size;
    OrthographicCamera* camera;
public:
    MainScreen();
    void create();
    void render();
    void update(float delta);
};

#endif // __MAINSCREEN_H__