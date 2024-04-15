#pragma once
#include <iostream>
#include <vector>

#include "InputEvent.h"
#include "AssetManager.h"
#include "Screen.h"
#include "SpriteRender.h"
#include "BasicRender.h"
#include <random>

typedef int RANDOM_NUM ;

class Game
{
public:
    GLint ScreenWidth;
    GLint ScreenHeight;
    float time = 0.f;
    float recent_delta = 0.f;
    int status;
    // std::random_device randSeed;
    unsigned int seed;
    

    virtual void setScreen(Screen*) = 0;
    virtual AssetManager* getAssetManager() = 0;
    virtual InputEvent* getInputEvent() = 0;
    virtual void create() = 0;
    virtual void render() = 0;
    virtual void update(float& delta) = 0;
    virtual SpriteRender* getSpriteRender() = 0;
    virtual void renderText(std::wstring&, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color ) = 0;
    virtual void sendEvent(LinkA_Event& event) = 0;
    virtual void resize(GLint&, GLint&) = 0;
    virtual RANDOM_NUM rand(RANDOM_NUM min, RANDOM_NUM max) = 0;
    virtual BasicRender * getBasicRender() = 0;

};