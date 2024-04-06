#include "game_obj/Board.h"
#include "LinkALog.h"


extern Game *game;

void Board::create()
{
    // 初始化一些数据
    cardGapx = 5.f;
    cardGapy = 5.f;
    cardWidth = 50.f;
    cardHeight = 50.f;
    cardsOrigin.x = 275;
    cardsOrigin.y = 50;
    ground = game->getAssetManager()->getTexture("back");
    position = glm::vec2(250, 25);
    size = glm::vec2(500, 500.f);

    // 10 * 10
    for (int x = 0; x < column * row; x++)
    {
        Card *tst = new Card();
        tst->compare_id = 1;
        if (x % 2 == 1)
        {
            tst->compare_id = 2;
        }
        tst->create();

        objs.push_back(tst);
    }
    this->updateLayout();

        BaseBoard_CardRecipient *main_recipient = new BaseBoard_CardRecipient();
    main_recipient->outer = this;
    // auto s= main_recipient::handleMessage;
    events->registListerner(_CARD_SELECTED, main_recipient);

}

void Board::render(Camera *camera)
{
    game->getSpriteRender()->DrawSprite(ground, position, camera->getProjectionMatrix(), camera->getViewMatrix(), size);

    for (Card *objPtr : objs)
    {
        objPtr->render(camera);
    }
}

void Board::update(float delta)
{
    for (auto it = objs.begin(); it != objs.end();)
    {
        Card *objPtr = (*it);
        if (objPtr->delFlag)
        {
            it = objs.erase(it);
            delete objPtr;
            objPtr = NULL;
        }
        else
        {
            objPtr->update(delta);
            it++;
        }
    }
}

void Board::onEvent(LinkA_Event &event)
{
    if (event.type == LinkA_EventType::MOUSE_PRESS)
    {
        // if (e.xpos >= position.x && e.xpos <= (position.x + size.x) && e.ypos >= position.y && e.ypos <= (position.y + size.y))
        // {
        //     // SPDLOG_LOGGER_INFO(LinkALog, "board was hit: [{}]  mods: [{}], position: x:{} - y: {}", e.mouseButton, e.mods,e.xpos,e.ypos);
        // }
    }

    for (Card *objPtr : objs)
    {
        if (!event.s)
        {
            break;
        }
        objPtr->onEvent(event);
    }
}

void Board::updateLayout()
{
    for (int i = 0; i < objs.size() && i < column * row; i++)
    {
        Card *objPtr = objs[i];
        int c_col = i % column;
        int c_row = i / column;

        objPtr->position.x = cardGapx * (c_col + 1) + cardWidth * c_col + cardsOrigin.x;
        objPtr->position.y = cardGapy * (c_row + 1) + c_row * cardHeight + cardsOrigin.y;

        objPtr->size.x = cardWidth;
        objPtr->size.y = cardHeight;
    }
}


bool Board::BaseBoard_CardRecipient::handleMessage(_LinkAMessage &msg)
{
    if (msg.messageType != _CARD_SELECTED)
    {
        return false;
    }
    if (outer->selected.size() > 0)
    {
        if (msg.extraInfo && dynamic_cast<Card *>(msg.extraInfo) )
        {
            Card *selecedCard = outer->selected[0];
            if (msg.extraInfo != selecedCard && selecedCard->compare_id == dynamic_cast<Card *>(msg.extraInfo)->compare_id)
            {
                selecedCard->status = GAME_STATUS::INVALID;
                dynamic_cast<Card *>(msg.extraInfo)->status = GAME_STATUS::INVALID;
                // delete selecedCard;
                // delete msg.extraInfo;
                // i need a GC
                msg.extraInfo->delFlag = true;
                selecedCard->delFlag = true;
            }
            else
            {
                selecedCard->status = GAME_STATUS::NORMAL;
            }
            outer->selected.erase(std::remove(outer->selected.begin(), outer->selected.end(), selecedCard), outer->selected.end());
        }
    }
    else if (dynamic_cast<Card *>(msg.extraInfo))
    {
        dynamic_cast<Card *>(msg.extraInfo)->status = Game_obj_status::PICKED;
        outer->selected.push_back(dynamic_cast<Card *>(msg.extraInfo));
    }
    return true;
}

void Board::dispose() {}