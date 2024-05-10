#ifndef __LEVELPICK_H__
#define __LEVELPICK_H__
#include "GameObject.h"
#include "Texture.h"

class LevelPicker : public GameObject
{
private:
public:
    Texture *pic;
    Texture *foreground;
    virtual void onEvent(LinkA_Event &__event);
    virtual void create();
    virtual void render(Camera *);
    virtual void update(float delta);
    virtual void dispose();
};

#endif // __LEVELPICK_H__