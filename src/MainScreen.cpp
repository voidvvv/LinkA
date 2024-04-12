#include "MainScreen.h"
#include <iostream>
#include "Game.h"
#include "game_obj/Card.h"
#include <algorithm>

#include "miscellaneous.h"
#include "Shader.h"
#include "OrthographicCamera.h"
#include "sound/SoundManager.h"

extern Game *game;
extern SoundPlayer* soundManager;

MainScreen::MainScreen()
{
}

void MainScreen::create()
{
    // events->dispose();

    // 加载资源
    camera = new OrthographicCamera(SCREEN_WIDTH, SCREEN_HEIGH);
    // face = game->getAssetManager()->getTexture("face");
    game->getAssetManager()->loadTexture("./img/beauti.png", "board");
    game->getAssetManager()->loadTexture("./img/background.jpg", "background");
    game->getAssetManager()->loadTexture("./img/back.png", "back");
    game->getAssetManager()->loadTexture("./img/card1.png", "card1");
    game->getAssetManager()->loadTexture("./img/card2.png", "card2");
    // obstacle
    game->getAssetManager()->loadTexture("./img/obstacle.jpg", "obstacle");

    // music
    game->getAssetManager()->loadMusic("./sound/xx.mp3","xx");
    // 加载数据
    board = new Board();
    board->create();

    _CardRecipient *main_recipient = new _CardRecipient();
    main_recipient->outer = this;
    events->registListerner(_CARD_SELECTED, main_recipient);

    soundManager->playBgm(game->getAssetManager()->getMusic("xx"));
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

    // render ui
}

void MainScreen::update(float delta)
{
    board->update(delta);
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
}

bool MainScreen::_CardRecipient::handleMessage(_LinkAMessage &msg)
{
    return false;
}
