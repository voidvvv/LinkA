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
#include "game_obj/Card.h"

class MainScreen : public Screen
{
private:


    GLfloat *pPointDepth = new float(1.f);
    glm::vec3 tmpV;
    Texture *face;
    Board *board;
    std::vector<Card *> objs;

    Camera *camera;

    int row = 8;
    int column = 8;

    glm::vec3 cardsOrigin;
    float cardGapx;
    float cardGapy;
    float cardWidth;
    float cardHeight;

public:
    MainScreen();
    void create();
    void render();
    void update(float delta);
    void dispose();
    void sendEvent(LinkA_Event &event);
    void updateLayout();
};

#endif // __MAINSCREEN_H__