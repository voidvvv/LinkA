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
    // 初始化一些数据
    cardGapx = 5.f;
    cardGapy = 5.f;
    cardWidth = 50.f;
    cardHeight = 50.f;
    cardsOrigin.x = 275;
    cardsOrigin.y = 50;
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

    // 10 * 10
    for (int x = 0; x < column * row; x++)
    {
        GameObject *tst = new Card();
        tst->create();
        objs.push_back(tst);
    }
    this->updateLayout();
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

        // glReadPixels(event.pos.x, event.pos.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, pPointDepth);

        tmpV.x = event.pos.x;
        tmpV.y = event.pos.y;
        tmpV.z = 0.f;
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

void MainScreen::updateLayout()
{
    for (int i = 0; i < objs.size() && i < column*row; i++){
        GameObject* objPtr =  objs[i];
        int c_col = i % column;
        int c_row = i/column;

        objPtr->position.x = cardGapx*(c_col+1) + cardWidth*c_col +cardsOrigin.x;
        objPtr->position.y = cardGapy*(c_row+1) + c_row * cardHeight + cardsOrigin.y;

        objPtr->size.x = cardWidth;
        objPtr->size.y = cardHeight;
    }
}
