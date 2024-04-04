#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "LinkAViewPort.h"
#include "Game.h"
#include "GameEvent.h"

extern GLFWwindow* window;
extern Game* game;
extern LinKAViewPort* linKA_viewport;

void start(Game* __game);