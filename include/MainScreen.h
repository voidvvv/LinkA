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
#include "GameEvent.h"

class MainScreen : public Screen
{
private:
// UI
    std::wstring s;
    std::wstring title;
    int score;

    GLfloat *pPointDepth = new float(1.f);
    glm::vec3 tmpV;
    Camera *camera;
    Board *board;



public:
    class _CardRecipient : public _Recipient
    {
    public:
        MainScreen *outer;
        virtual bool handleMessage(_LinkAMessage &msg);
    };
    MainScreen();
    void create();
    void render();
    void update(float delta);
    void dispose();
    void sendEvent(LinkA_Event &event);

};

#endif // __MAINSCREEN_H__