#include "MainScreen.h"
#include <iostream>
#include "Game.h"
#include "game_obj/Card.h"
#include <algorithm>
#include <OrthographicCamera.h>
#include "miscellaneous.h"
#include "Shader.h"
#include "../include/CameraController.h"

#include "sound/SoundManager.h"

extern Game *game;
extern SoundPlayer *soundManager;

MainScreen::MainScreen()
{
}

void MainScreen::create()
{
    // events->dispose();
    const float width = SCREEN_WIDTH;
    const float height = SCREEN_HEIGH;
    // 加载资源
    camera = new OrthographicCamera(width, height);
    cameracontrol::addController(camera);
    game->getAssetManager()->loadTexture("./img/beauti.png", "board");
    game->getAssetManager()->loadTexture("./img/background.jpg", "background");
    game->getAssetManager()->loadTexture("./img/back.png", "back");
    game->getAssetManager()->loadTexture("./img/card1.png", "card1");
    game->getAssetManager()->loadTexture("./img/card2.png", "card2");
    game->getAssetManager()->loadTexture("./img/card3.png", "card3");
    game->getAssetManager()->loadTexture("./img/card4.png", "card4");

    game->getAssetManager()->loadTexture("./img/skybox/back.jpg", "skybox_back");
    game->getAssetManager()->loadTexture("./img/skybox/bottom.jpg", "skybox_bottom");

    game->getAssetManager()->loadTexture("./img/skybox/front.jpg", "skybox_front");

    game->getAssetManager()->loadTexture("./img/skybox/left.jpg", "skybox_left");

    game->getAssetManager()->loadTexture("./img/skybox/back.jpg", "skybox_back");

    game->getAssetManager()->loadTexture("./img/skybox/back.jpg", "skybox_back");

    // obstacle
    game->getAssetManager()->loadTexture("./img/obstacle.jpg", "obstacle");

    // music
    game->getAssetManager()->loadMusic("./sound/bgm.mp3", "bgm");
    game->getAssetManager()->loadMusic("./sound/chipLay1.wav", "chipLay1");
    game->getAssetManager()->loadMusic("./sound/foom_0.wav", "foom_0");
    // 加载数据
    board = new Board();
    board->create();

    _CardRecipient *main_recipient = new _CardRecipient();
    main_recipient->outer = this;
    events->registListerner(_CARD_SELECTED, main_recipient);
    // _CARD_SUCCESS_MATCH_GLOBAL
    events->registListerner(_CARD_SUCCESS_MATCH_GLOBAL, main_recipient);

    soundManager->playBgm(game->getAssetManager()->getMusic("bgm"));
    title = L"茜茜连连看";
    score = 0;
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
    game->renderText(title, 20, 500, 1, glm::vec3(0.5f));
    std::wstring wStrscore = L"分数: " + std::to_wstring(score);
    game->renderText(wStrscore, 20, 400, 1, glm::vec3(1.f));
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
        std::cout << tmpV.x << " - " << tmpV.y<< " - " << tmpV.z << std::endl;
                std::cout << worldPos.x << " - " << worldPos.y<< " - " << worldPos.z << std::endl;

        event.world_pos = worldPos;
    }
    // LinkA_EventType::KEY_BOARD_PRESS,LinkA_FuncKey::BASE_FUNC
    if (event.type == LinkA_EventType::KEY_BOARD_PRESS && event.func == LinkA_FuncKey::BASE_FUNC)
    {
        board->dispose();
        board->create();
        score = 0;
    }
    board->onEvent(event);
}

bool MainScreen::_CardRecipient::handleMessage(_LinkAMessage &msg)
{
    if (msg.messageType == _CARD_SUCCESS_MATCH_GLOBAL)
    {
        outer->score++;
        return true;
    }
    return false;
}
