#include "game_obj/Board.h"
#include "LinkALog.h"

extern Game *game;

void Board::create()
{
    ground = game->getAssetManager()->getTexture("back");
    position = glm::vec2(250, 25);
    size = glm::vec2(500, 500.f);
}

void Board::render(Camera *camera)
{
    game->getSpriteRender()->DrawSprite(ground, position, camera->getProjectionMatrix(), camera->getViewMatrix(), size);
}

void Board::update(float delta)
{
}

void Board::onEvent(LinkA_Event &e)
{
    if (e.type == LinkA_EventType::MOUSE_PRESS)
    {
        // if (e.xpos >= position.x && e.xpos <= (position.x + size.x) && e.ypos >= position.y && e.ypos <= (position.y + size.y))
        // {
        //     // SPDLOG_LOGGER_INFO(LinkALog, "board was hit: [{}]  mods: [{}], position: x:{} - y: {}", e.mouseButton, e.mods,e.xpos,e.ypos);
        // }
    }
}