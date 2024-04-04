#include "MainScreen.h"
#include <iostream>
#include "Game.h"
#include "game_obj/Card.h"

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
    game->getAssetManager()->loadTexture("./img/back.png", "back");
    game->getAssetManager()->loadTexture("./img/card1.png", "card1");
    // 加载数据
    board = new Board();
    board->create();

    GameObject *tst = new Card();
    tst->create();

    objs.push_back(tst);
}

void MainScreen::render()
{
    // glClearColor(0.56f, 0, 0.56f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = camera->getProjectionMatrix();
    // render bg
    game->getSpriteRender()->DrawSprite(game->getAssetManager()->getTexture("background"), glm::vec2(0, 0), projection, view, glm::vec2(SCREEN_WIDTH, SCREEN_HEIGH));

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

void MainScreen::sendEvent(LinkA_Event &event)
{
    if (isMouse(&event))
    {
        
        glReadPixels(event.pos.x, event.pos.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, pPointDepth);
        
        tmpV.x = event.pos.x;
        tmpV.y = event.pos.y;
        tmpV.z = *pPointDepth;
        glm::vec3 worldPos = camera->unproject(this->tmpV);
        event.world_pos = worldPos;
    }
    board->onEvent(event);
    for (GameObject *objPtr : objs)
    {
        if (!event.s)
        {
            break;
        }
        objPtr->onEvent(event);
    }
}
