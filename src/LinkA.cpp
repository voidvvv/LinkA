#include "LinkA.h"
#include "Game.h"
#include "miscellaneous.h"


void position_callback(GLFWwindow *window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_event_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

GLFWwindow *window;
Game* game;

float lastTime;
void start(Game* __game)
{
    game = __game;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window =
        glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGH, "Hi 0307", NULL, NULL);
    if (!window)
    {
        std::cout << "window error!" << std::endl;
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_event_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    lastTime = glfwGetTime();
    game->create();
    while (!glfwWindowShouldClose(window))
    {
        float cur = glfwGetTime();
        float delta = cur - lastTime;
        game->time = game->time + delta;
        game->recent_delta = delta;
        game->update(delta);
        game->render();
        lastTime = cur;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}


void position_callback(GLFWwindow *window, double xpos, double ypos)
{
    game->getInputEvent()->mouseMove(xpos,ypos);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0,0,width,height);
}

void key_event_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
        game->getInputEvent()->keyEvent(key,scancode,action,mods);

}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
            game->getInputEvent()->mouseButton(button,action,mods);
}
