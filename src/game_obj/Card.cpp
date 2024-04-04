#include "game_obj/Card.h"
#include "ObjUtil.h"
#include <iostream>

void Card::onEvent(LinkA_Event &event)
{
    if (event.type == LinkA_EventType::MOUSE_PRESS)
    {
        if (contain(this, event))
        {
            // send message

        }
        else
        {
        }
    }
    else if (event.type == LinkA_EventType::MOUSE_RELEASE)
    {
    }
    else if (event.type == LinkA_EventType::MOUSE_MOVE)
    {
    }
}

void Card::create()
{
    std::stringstream ss ;
    ss << "card"<< compare_id;

    // init img
    img = game->getAssetManager()->getTexture(ss.str());
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

}
