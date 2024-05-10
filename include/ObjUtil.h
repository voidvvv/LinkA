#ifndef __OBJUTIL_H__
#define __OBJUTIL_H__
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GameObject.h"
#include "InputEvent.h"
class GameObject;
class LinkA_Event;

class Game;
class LinKAViewPort;
class _LinkAGameEvents;
class SoundPlayer;

extern GLFWwindow *window;
extern Game *game;
extern LinKAViewPort *linKA_viewport;
extern _LinkAGameEvents *events;
extern SoundPlayer* soundManager;

bool contain(GameObject*, LinkA_Event&);
#endif // __OBJUTIL_H__