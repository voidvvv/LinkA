#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "InputEvent.h"

#include "Camera.h"
// this is the root object for all game obj
enum GAME_STATUS
{
    CREATE,
    NORMAL,
    INVALID
};

class GameObject
{
public:
    GAME_STATUS status;
    glm::vec2 position;
    glm::vec2 size;

    virtual void onEvent(LinkA_Event& __event) = 0;
    virtual void create() = 0;
    virtual render(Camera *) = 0;
    virtual update(float delta) = 0;
};

#endif // __GAMEOBJECT_H__