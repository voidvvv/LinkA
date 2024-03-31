#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class InputEvent{
public:
    double xpos;
    double ypos;
    void mouseMove(double x, double y);
    void keyEvent( int key, int scancode, int action, int mods);
    void mouseButton(int button, int action, int mods);
};