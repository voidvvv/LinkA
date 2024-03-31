#include "MainScreen.h"
#include <iostream>
#include "Game.h"

#include "miscellaneous.h"
#include "Shader.h"

extern Game *game;

MainScreen::MainScreen()
{
}

void MainScreen::create()
{
    camera = new OrthographicCamera(SCREEN_WIDTH, SCREEN_HEIGH);
    face = game->getAssetManager()->getTexture("face");
}

void MainScreen::render()
{
    glClearColor(0.56f, 0, 0.56f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = camera->getProjectionMatrix();
    game->getSpriteRender()->DrawSprite(face,glm::vec2(10,10),projection,view,glm::vec2(100,100));

}

void MainScreen::update(float delta)
{
}

void MainScreen::dispose()
{
    
}
