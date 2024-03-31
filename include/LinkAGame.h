#pragma once
#include "Game.h"
#include "Screen.h"
#include "AssetManager.h"
#include "TextApplication.h"

class LinkAGame : public Game
{
private:
    InputEvent *contro;
    CharacterManager *textManager;
    SpriteRender* renderer;

public:
    Screen *scn;
    AssetManager *assetManager;

    void create() override;
    InputEvent *getInputEvent() override;
    void render() override;
    void update(float &delta) override;
    AssetManager *getAssetManager() override;
    void renderText(std::wstring&, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) override;
    void setScreen(Screen*) override;
    SpriteRender* getSpriteRender() override;
    void sendEvent(LinkA_Event& event) override;
};