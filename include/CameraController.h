#ifndef __CAMERACONTROLLER_H__
#define __CAMERACONTROLLER_H__
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Camera.h"

namespace cameracontrol
{
    class CameraController
    {
    public:
        Camera *camera;

        bool mouseFirst;
        float lastX;
        float lastY;

        bool upMove;
        bool downMove;
        bool frontMove;
        bool backMove;
        bool leftMove;
        bool rightMove;

        void onKeyPress(int key, int action, int mod);

        void onMouseMove(double x, double y);

        void onScroll(float xOffset, float yOffset);

        void update(float delta);
    };
    extern std::vector<CameraController *> controllers;

    void addController(Camera *);

    void onKeyPress(int key, int action, int mod);

    void onMouseMove(double x, double y);

    void onScroll(float xOffset, float yOffset);

    void update(float delta);
}
#endif // __CAMERACONTROLLER_H__