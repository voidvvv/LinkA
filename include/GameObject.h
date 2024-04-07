#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Game.h"

#include "InputEvent.h"

#include "Camera.h"


extern Game* game;
// this is the root object for all game obj
typedef enum GAME_STATUS
{
    CREATE,
    PICKED,
    NORMAL,
    INVALID
} Game_obj_status;

class GameObject
{
public:
    Game_obj_status status;
    bool delFlag = false; // wait to be delete as pointer
    glm::vec2 position;
    glm::vec2 size;
    glm::vec2 center;
    /*
        input event
    */
    virtual void onEvent(LinkA_Event& __event) = 0;
    virtual void create() = 0;
    virtual void render(Camera *) = 0;
    virtual void update(float delta) = 0;
};

#endif // __GAMEOBJECT_H__