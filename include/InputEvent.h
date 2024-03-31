#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

enum LinkA_EventType
{
    KEY_BOARD_PRESS,
    KEY_BOARD_RELEASE,
    MOUSE_MOVE,
    MOUSE_PRESS,
    MOUSE_RELEASE
};

enum LinkA_FuncKey
{

};
class LinkA_Event
{
public:
    bool s;
    double xpos;
    double ypos;
    LinkA_FuncKey func;

    LinkA_EventType type;
    int mouseButton;
    int mods;

};

class InputEvent
{
private:
    void sendMouseEvent(LinkA_EventType,int button, int mods);
public:
    double xpos;
    double ypos;

    std::vector<LinkA_Event> cache;
    InputEvent();
    void mouseMove(double x, double y);
    void keyEvent(int key, int scancode, int action, int mods);
    void mouseButton(int button, int action, int mods);
};