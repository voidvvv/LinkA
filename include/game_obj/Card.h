#ifndef __CARD_H__
#define __CARD_H__
#include "GameObject.h"
#include "Texture.h"

enum PULL_STATUS
{
    NONE,
    PULL
};

class Card : public GameObject
{
    Texture *img;
    PULL_STATUS ps = PULL_STATUS::NONE;
    glm::vec2 postion_delta;

    virtual void onEvent(LinkA_Event &__event);
    virtual void create();
    virtual void render(Camera *);
    virtual void update(float delta);
};

#endif // __CARD_H__