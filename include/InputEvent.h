#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    glm::vec3 pos;
    glm::vec3 world_pos;
    LinkA_FuncKey func;

    LinkA_EventType type;
    int mouseButton;
    int mods;
};

class InputEvent
{
private:
    void sendMouseEvent(LinkA_EventType, int button, int mods);

public:
    glm::vec3 pos;
    std::vector<LinkA_Event> cache;
    InputEvent();
    void mouseMove(double x, double y);
    void keyEvent(int key, int scancode, int action, int mods);
    void mouseButton(int button, int action, int mods);
    void update(float dalta);
};

bool isMouse(LinkA_Event *);