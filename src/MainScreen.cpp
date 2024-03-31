#include "MainScreen.h"
#include <iostream>
#include "Game.h"

#include "miscellaneous.h"
#include "Shader.h"
#include "OrthographicCamera.h"

extern Game *game;

MainScreen::MainScreen()
{
}

void MainScreen::create()
{
    // 加载资源
    camera = new OrthographicCamera(SCREEN_WIDTH, SCREEN_HEIGH);
    // face = game->getAssetManager()->getTexture("face");
    game->getAssetManager()->loadTexture("./img/beauti.png", "board");
    game->getAssetManager()->loadTexture("./img/background.jpg", "background");

    // 加载数据
    board = new Board();
    board->create();
}

void MainScreen::render()
{
    // glClearColor(0.56f, 0, 0.56f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = camera->getProjectionMatrix();
        // render bg
    game->getSpriteRender()->DrawSprite(game->getAssetManager()->getTexture("background"), glm::vec2(0, 0), projection, view, glm::vec2(SCREEN_WIDTH, SCREEN_HEIGH));


    // game->getSpriteRender()->DrawSprite(face, glm::vec2(10, 10), projection, view, glm::vec2(1.f));
    std::wstring ws = L"ASASD我爱中华";
    game->renderText(ws,10,10,2,glm::vec3(1,0,0));
    // draw board
    board->render(camera);
    for (GameObject *objPtr : objs)
    {
        objPtr->render(camera);
    }
}

void MainScreen::update(float delta)
{
    board->update(delta);
    for (GameObject *objPtr : objs)
    {
        objPtr->update(delta);
    }
}

void MainScreen::dispose()
{
}

void MainScreen::sendEvent(LinkA_Event& event)
{
    board->onEvent(event);
    for (GameObject *objPtr : objs)
    {
        if (!event.s){
            break;
        }
        objPtr->onEvent(event);
    }
}
