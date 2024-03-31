#include "game_obj/Board.h"

extern Game* game;

void Board::create()
{
    ground = game->getAssetManager()->getTexture("board");
    position = glm::vec2(20,20);
    size = glm::vec2(600,500.f);
}

Board::render(Camera * camera)
{
    game->getSpriteRender()->DrawSprite(ground,position,camera->getProjectionMatrix(),camera->getViewMatrix(),size);
}

Board::update(float delta)
{
    size.x+=(delta*10);
}

void Board::onEvent(LinkA_Event& e)
{
    if (e.type == LinkA_EventType::MOUSE_PRESS){
        if (e.xpos >= position.x && e.xpos <= (position.x + size.x) && e.ypos >= position.y && e.ypos <= (position.y + size.y)){
            std::cout << "board was hit: ["<< e.mouseButton<<"]  mods: "<< e.mods <<std::endl;
        }
    }
}