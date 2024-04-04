#ifndef __MAINSCREEN_H__
#define __MAINSCREEN_H__
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Screen.h"
#include "Texture.h"
#include "Camera.h"
#include "TextApplication.h"
#include "GameObject.h"
#include "game_obj/Board.h"

class MainScreen : public Screen
{
private:
    GLfloat * pPointDepth = new float(1.f);
    glm::vec3 tmpV;
    Texture *face;
    Board *board;
    std::vector<GameObject *> objs;

    Camera *camera;

public:
    MainScreen();
    void create();
    void render();
    void update(float delta);
    void dispose();
    void sendEvent(LinkA_Event &event);
};

#endif // __MAINSCREEN_H__