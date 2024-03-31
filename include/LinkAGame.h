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

public:
    Screen *scn;
    AssetManager *assetManager;
    LinkAGame();
    void create() override;
    InputEvent *getInputEvent() override;
    void render() override;
    void update(float &delta) override;
    AssetManager *getAssetManager() override;
    void renderText(std::wstring&, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) override;
};