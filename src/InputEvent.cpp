#include "InputEvent.h"
#include "miscellaneous.h"
#include "Game.h"
#include <iostream>

extern Game *game;

void InputEvent::mouseMove(double x, double y)
{
    this->xpos = static_cast<float>(x);
    this->ypos = static_cast<float>(SCREEN_HEIGH - y);

    sendMouseEvent(LinkA_EventType::MOUSE_MOVE,-1,-1);
}

void InputEvent::keyEvent(int key, int scancode, int action, int mods)
{
}

void InputEvent::mouseButton(int button, int action, int mods)
{
    if (action == GLFW_RELEASE)
    {
        sendMouseEvent(LinkA_EventType::MOUSE_RELEASE,button,mods);
    }else if (action == GLFW_PRESS){
        sendMouseEvent(LinkA_EventType::MOUSE_PRESS,button,mods);
    }
}
InputEvent::InputEvent()
{
    for (int x = 0; x < 100; x++)
    {
        LinkA_Event e;
        cache.push_back(e);
    }
}

void InputEvent::sendMouseEvent(LinkA_EventType eventType, int button, int mods)
{
    if (cache.size() > 0)
    {
        LinkA_Event e = cache.back();
        cache.pop_back();
        e.type = eventType;
        e.s = false;
        e.xpos = this->xpos;
        e.ypos = this->ypos;
        e.mouseButton = button;
        e.mods = mods;
        game->sendEvent(e);
        cache.push_back(e);
    }
    else
    {
        LinkA_Event e;
        e.type = eventType;
        e.s = false;
        e.xpos = this->xpos;
        e.ypos = this->ypos;
        e.mouseButton = button;
        e.mods = mods;
        game->sendEvent(e);
    }
}
