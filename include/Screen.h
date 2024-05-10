#ifndef __SCREEN_H__
#define __SCREEN_H__
#include "InputEvent.h"



class Screen
{
public:
    virtual void create() = 0;
    virtual void render() = 0;
    virtual void update(float delta) = 0;
    virtual void dispose() = 0;
    virtual void sendEvent(LinkA_Event& event) = 0;
};

#endif // __SCREEN_H__