#include "game_obj/Card.h"
#include "ObjUtil.h"
#include <thread>

void Card::onEvent(LinkA_Event &event)
{
    if (event.type == LinkA_EventType::MOUSE_PRESS)
    {
        if (contain(this, event))
        {
            ps = PULL_STATUS::PULL;
            record_position.x = event.world_pos.x;
            record_position.y = event.world_pos.y;
            event.s = false;
        }
        else
        {
            ps = PULL_STATUS::NONE;
            event.s = true;
        }
    }
    else if (event.type == LinkA_EventType::MOUSE_RELEASE)
    {
        ps = PULL_STATUS::NONE;
        this->postion_delta.x = 0;
        this->postion_delta.y = 0;
    }
    else if (event.type == LinkA_EventType::MOUSE_MOVE)
    {
        if (this->ps == PULL_STATUS::PULL)
        {
            this->postion_delta.x += (event.world_pos.x - record_position.x);
            this->postion_delta.y += (event.world_pos.y - record_position.y);
            record_position.x = event.world_pos.x;
            record_position.y = event.world_pos.y;
        }
    }
}

void Card::create()
{
    // init img
    img = game->getAssetManager()->getTexture("card1");
    size = glm::vec2(50, 50);
}

void Card::render(Camera *cam)
{
    glm::mat4 projection = cam->getProjectionMatrix();
    glm::mat4 view = cam->getViewMatrix();
    game->getSpriteRender()->DrawSprite(img, position, projection, view, size);
}

void Card::update(float delta)
{
    if (ps == PULL_STATUS::PULL)
    {
        std::cout << "pull x: " << this->position.x << " - y: " << this->position.y << std::endl;
        this->position.x += this->postion_delta.x;
        this->position.y += this->postion_delta.y;

        this->postion_delta.x = this->postion_delta.y = 0.f;
    }
}
