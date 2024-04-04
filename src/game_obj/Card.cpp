#include "game_obj/Card.h"
#include "ObjUtil.h"
#include <iostream>

extern _LinkAGameEvents* events;

void Card::onEvent(LinkA_Event &event)
{
    if (event.type == LinkA_EventType::MOUSE_PRESS)
    {
        if (contain(this, event))
        {
            // send message
            events->sendMessaage(_CARD_SELECTED,nullptr,NULL,this);
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
    this->PickedColor.x = this->PickedColor.y = this->PickedColor.z = 0.5;
    this->NormalColor.x = this->NormalColor.y = this->NormalColor.z = 1.f;
    // init img
    img = game->getAssetManager()->getTexture(ss.str());
    size = glm::vec2(50, 50);
}

void Card::render(Camera *cam)
{
    glm::vec3 color = NormalColor;
    if (this->status == Game_obj_status::PICKED){
        color = PickedColor;
    }
    glm::mat4 projection = cam->getProjectionMatrix();
    glm::mat4 view = cam->getViewMatrix();
    game->getSpriteRender()->DrawSprite(img, position, projection, view, size,0.f,color);
}

void Card::update(float delta)
{

}
