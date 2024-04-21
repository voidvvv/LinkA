#include "../include/CameraController.h"
#include <iostream>

using namespace cameracontrol;

std::vector<CameraController *> cameracontrol::controllers;

static void setMoveAction(int key, int action, int keyTarget, int actionA, int actionB, bool &f)
{
    if (key == keyTarget)
    {
        if (action == actionA)
        {
            f = true;
        }
        else if (action == actionB)
        {
            f = false;
        }
    }
}

void cameracontrol::CameraController::onKeyPress(int key, int action, int mod)
{
    if (action == GLFW_PRESS)
    {
        std::cout << "on key press for camera controller" << std::endl;
    }else if ( action == GLFW_REPEAT) {
        std::cout << "on key REPEAT for camera controller" << std::endl;
    }
    setMoveAction(key, action, GLFW_KEY_W, GLFW_PRESS, GLFW_RELEASE, frontMove);
    setMoveAction(key, action, GLFW_KEY_S, GLFW_PRESS, GLFW_RELEASE, backMove);
    setMoveAction(key, action, GLFW_KEY_A, GLFW_PRESS, GLFW_RELEASE, leftMove);
    setMoveAction(key, action, GLFW_KEY_D, GLFW_PRESS, GLFW_RELEASE, rightMove);
}

void cameracontrol::CameraController::onMouseMove(double x, double y)
{
    float xF = static_cast<float>(x);
    float yF = static_cast<float>(y);
    if (mouseFirst)
    {
        lastX = xF;
        lastY = yF;
        mouseFirst = false;
    }
    float xOffset = xF - lastX;
    float yOffset = lastY - yF;

    lastX = xF;
    lastY = yF;
    camera->Yaw += (xOffset * 0.1F);
    camera->Pitch += (yOffset * 0.1F);
    camera->update();
}

void cameracontrol::CameraController::onScroll(float xOffset, float yOffset)
{
    camera->Zoom -= (float)yOffset;
    if (camera->Zoom < 1.0f)
        camera->Zoom = 1.0f;
    if (camera->Zoom > 45.0f)
        camera->Zoom = 45.0f;
    camera->update();
}

void cameracontrol::CameraController::update(float delta)
{
    if (frontMove)
    {
        camera->position += (camera->direct * delta);
    }
    else if (backMove)
    {
        camera->position -= (camera->direct * delta);
    }

    if (leftMove)
    {
        camera->position -= (camera->right * delta);
    }
    else if (rightMove)
    {
        camera->position += (camera->right * delta);
    }
    camera->update();
}

void cameracontrol::addController(Camera *cam)
{
    CameraController *control = new CameraController();
    control->camera = cam;
    controllers.push_back(control);
}

void cameracontrol::onKeyPress(int key, int action, int mod)
{

    for (CameraController *control : controllers)
    {
        control->onKeyPress(key, action, mod);
    }
}

void cameracontrol::onMouseMove(double x, double y)
{
    for (CameraController *control : controllers)
    {
        control->onMouseMove(x, y);
    }
}

void cameracontrol::onScroll(float xOffset, float yOffset)
{
    for (CameraController *control : controllers)
    {
        control->onScroll(xOffset, yOffset);
    }
}

void cameracontrol::update(float delta)
{
    for (CameraController *control : controllers)
    {
        control->update(delta);
    }
}
