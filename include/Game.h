#pragma once
#include <iostream>
#include <vector>
#include "InputEvent.h"
#include "AssetManager.h"
#include "Screen.h"
#include "SpriteRender.h"

class Game
{
public:
    float time = 0.f;
    float recent_delta = 0.f;
    int status;

    virtual void setScreen(Screen*) = 0;
    virtual AssetManager* getAssetManager() = 0;
    virtual InputEvent* getInputEvent() = 0;
    virtual void create() = 0;
    virtual void render() = 0;
    virtual void update(float& delta) = 0;
    virtual SpriteRender* getSpriteRender() = 0;
    virtual void renderText(std::wstring&, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color ) = 0;
};