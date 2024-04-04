#include "LinkA.h"
#include "Game.h"
#include "miscellaneous.h"
#include "LinkALog.h"
#include "GameEvent.h"

void position_callback(GLFWwindow *window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_event_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

GLFWwindow *window;
Game *game;
LinKAViewPort *linKA_viewport;
_LinkAGameEvents* events;

float lastTime;

void initLogger()
{
    // Create a file rotating logger with 5 MB size max and 3 rotated files
    auto max_size = 1048576 * 5;
    auto max_files = 3;
    auto _LinkA_Logger = spdlog::rotating_logger_mt("LinkALogger", "logs/rotating.txt", max_size, max_files);
    _LinkA_Logger->set_level(spdlog::level::debug);
    _LinkA_Logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e][thread %t][%@,%!][%l] : %v");

    spdlog::flush_every(std::chrono::seconds(1)); // 定期刷新日志缓冲区
}

void start(Game *__game)
{
    game = __game;
    linKA_viewport = new LinKAViewPort();
    initLogger();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window =
        glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGH, "Hi LinkA", NULL, NULL);
    if (!window)
    {
        LinkALog->info("window error!");
        SPDLOG_LOGGER_INFO(LinkALog, "window error!");
        return;
    }
    // linKA_viewport->apply(0, 0, SCREEN_WIDTH, SCREEN_HEIGH);
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
    framebuffer_size_callback(window, SCREEN_WIDTH, SCREEN_HEIGH);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    lastTime = glfwGetTime();
    game->create();
    events = new _LinkAGameEvents();
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
    game->getInputEvent()->mouseMove(xpos, ypos);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    linKA_viewport->apply(0, 0, width, height);
    game->resize(width, height);
}

void key_event_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    game->getInputEvent()->keyEvent(key, scancode, action, mods);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    game->getInputEvent()->mouseButton(button, action, mods);
}
