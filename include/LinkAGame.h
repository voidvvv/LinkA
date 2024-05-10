#pragma once
#include "Game.h"
#include "Screen.h"
#include "AssetManager.h"
#include "TextApplication.h"

#include <stack>


class LinkAGame : public Game
{
private:
    InputEvent *contro;
    CharacterManager *textManager;
    SpriteRender *renderer;
    BasicRender *basicRender;

public:
    Screen *scn;
    std::stack<Screen *> screen_stack;
    AssetManager *assetManager;

    void create() override;
    InputEvent *getInputEvent() override;
    void render() override;
    void update(float &delta) override;
    AssetManager *getAssetManager() override;
    void renderText(std::wstring &, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) override;
    void setScreen(Screen *) override;
    void replaceScreen(Screen *) ;
    SpriteRender *getSpriteRender() override;
    BasicRender * getBasicRender() override;
    void sendEvent(LinkA_Event &event) override;
    virtual void resize(GLint &, GLint &) override;
    virtual RANDOM_NUM rand(RANDOM_NUM min, RANDOM_NUM max) override;
};