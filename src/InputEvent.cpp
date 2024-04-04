#include "InputEvent.h"
#include "miscellaneous.h"
#include "Game.h"
#include <iostream>


extern Game *game;
extern GLFWwindow *window;
void InputEvent::mouseMove(double x, double y)
{
    // this->delta_x = (x - xpos);
    // this->delta_y = (SCREEN_HEIGH - y - ypos);

    this->pos.x = static_cast<float>(x);
    
    this->pos.y = static_cast<float>(game->ScreenHeight - y);

    sendMouseEvent(LinkA_EventType::MOUSE_MOVE, -1, -1);

}

void InputEvent::keyEvent(int key, int scancode, int action, int mods)
{
}

void InputEvent::mouseButton(int button, int action, int mods)
{
    if (action == GLFW_RELEASE)
    {
        sendMouseEvent(LinkA_EventType::MOUSE_RELEASE, button, mods);
    }
    else if (action == GLFW_PRESS)
    {
        sendMouseEvent(LinkA_EventType::MOUSE_PRESS, button, mods);
    }
}

void InputEvent::update(float dalta)
{
    // this->last_xpos = xpos;
    // this->last_ypos = ypos;

    // glfwGetCursorPos(window,&(this->xpos),&(this->ypos));
    // this->ypos = SCREEN_HEIGH - this->ypos;
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
        e.pos = this->pos;
        e.mouseButton = button;
        e.mods = mods;
        e.s = true;
        game->sendEvent(e);
        cache.push_back(e);
    }
    else
    {
        LinkA_Event e;
        e.type = eventType;
        e.s = true;
        e.pos = this->pos;
        e.mouseButton = button;
        e.mods = mods;
        game->sendEvent(e);
    }
}

bool isMouse(LinkA_Event* e)
{
    //     MOUSE_MOVE,
    // MOUSE_PRESS,
    // MOUSE_RELEASE
    return e->type == LinkA_EventType::MOUSE_MOVE || e->type == LinkA_EventType::MOUSE_PRESS || e->type == LinkA_EventType::MOUSE_RELEASE;
}
