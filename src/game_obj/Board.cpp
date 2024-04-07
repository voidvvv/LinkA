#include "game_obj/Board.h"
#include "LinkALog.h"

extern Game *game;

float Game_Heuristic(Card *, Card *)
{
    return 1.f;
}

bool Game_ShouldStop(Card *a, Card *b)
{
    return a == b;
}

void Board::create()
{
    int scale = 2;
    // 初始化一些数据
    cardGapx = 5.f / scale;
    cardGapy = 5.f / scale;
    cardWidth = 50.f / scale;
    cardHeight = 50.f / scale;

    this->column *= scale;
    this->row *= scale;

    cardsOrigin.x = 275;
    cardsOrigin.y = 50;
    ground = game->getAssetManager()->getTexture("back");
    position = glm::vec2(250, 25);
    size = glm::vec2(500, 500.f);

    pathFinder = new AStarPathFinder<Card>();
    graph = new LinkCardAGraph();
    graph->create();
    for (int x = 0; x < column * row; x++)
    {
        Card *tst = new Card();
        int x_pos = x % column;
        int y_pos = x / column;
        tst->x = x_pos;
        tst->y = y_pos;
        tst->index = x;
        tst->compare_id = 1;
        if (x % 2 == 1)
        {
            tst->compare_id = 2;
        }
        if (x_pos == y_pos){
            tst->nodeType = LinkANodeType::OBSTACLE;
        }
        tst->create();
        std::shared_ptr<Card> ptr(tst);
        ptrMapping[tst] = ptr;
        objs.push_back(ptr);
        this->graph->nodeVector.push_back(tst);
    }

    this->updateLayout();
    pathFinder->init(graph);
    BaseBoard_CardRecipient *main_recipient = new BaseBoard_CardRecipient();
    main_recipient->outer = this;
    events->registListerner(_CARD_SELECTED, main_recipient);
}

void Board::render(Camera *camera)
{
    game->getSpriteRender()->DrawSprite(ground, position, camera->getProjectionMatrix(), camera->getViewMatrix(), size);

    for (std::shared_ptr<Card> objPtr : objs)
    {
        objPtr.get()->render(camera);
    }
}

void Board::update(float delta)
{
    for (auto it = objs.begin(); it != objs.end();)
    {
        std::shared_ptr<Card> objPtr = (*it);
        if (objPtr.get()->delFlag)
        {
            it = objs.erase(it);
            objPtr.reset();
        }
        else
        {
            objPtr.get()->update(delta);
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

    for (std::shared_ptr<Card> objPtr : objs)
    {
        if (!event.s)
        {
            break;
        }
        objPtr.get()->onEvent(event);
    }
}

void addConnection(Card *from, Card *to)
{
    LinkACardConnection *conPtr = new LinkACardConnection();
    conPtr->fromNode = from;
    conPtr->toNode = to;
    from->connections.push_back(conPtr);
}

void Board::updateLayout()
{
    for (int i = 0; i < objs.size() && i < column * row; i++)
    {
        std::shared_ptr<Card> objPtr = objs[i];
        int c_col = i % column;
        int c_row = i / column;

        objPtr.get()->position.x = cardGapx * (c_col + 1) + cardWidth * c_col + cardsOrigin.x;
        objPtr.get()->position.y = cardGapy * (c_row + 1) + c_row * cardHeight + cardsOrigin.y;

        objPtr.get()->size.x = cardWidth;
        objPtr.get()->size.y = cardHeight;

        if (c_col + 1 < column)
        {
            addConnection(objPtr.get(), objs[i + 1].get());
        }
        if (c_col - 1 >= 0)
        {
            addConnection(objPtr.get(), objs[i - 1].get());
        }
        if (c_row + 1 < row)
        {
            addConnection(objPtr.get(), objs[i + column].get());
        }
        if (c_row - 1 >= 0)
        {
            addConnection(objPtr.get(), objs[i - column].get());
        }
    }
}

std::shared_ptr<Card> Board::findCardPtrByInfo(CardInfo *ci)
{
    return ptrMapping[ci->cPtr];
}

bool Board::BaseBoard_CardRecipient::handleMessage(_LinkAMessage &msg)
{
    if (msg.messageType != _CARD_SELECTED)
    {
        return false;
    }
    CardInfo *cardInfo = NULL;
    if (outer->selected.size() > 0)
    {
        std::shared_ptr<Card> selecedCard = outer->selected[0];
        outer->selected.erase(std::remove(outer->selected.begin(), outer->selected.end(), selecedCard), outer->selected.end());

        if (msg.extraInfo && (cardInfo = dynamic_cast<CardInfo *>(msg.extraInfo)) && cardInfo->nodeType == LinkANodeType::CARD)
        {
            std::shared_ptr<Card> extraCard = outer->findCardPtrByInfo(cardInfo);
            if (extraCard.get() != selecedCard.get() && selecedCard.get()->compare_id == extraCard.get()->compare_id)
            {
                // check type success
                std::vector<Card *> outPath;
                bool b = outer->pathFinder->searchNodePath(extraCard.get(), selecedCard.get(), Game_Heuristic, Game_ShouldStop, outPath);
                std::cout << "A: X - [" << extraCard.get()->x << "]  Y - [" << extraCard.get()->y << "]  B: x - [" << selecedCard.get()->x << "]   y- [" << selecedCard.get()->y << "] reseult: " << b << std::endl;

                if (b)
                {
                    events->sendMessaage(_CARD_SUCCESS_MATCH, NULL, extraCard.get(), outer);
                    events->sendMessaage(_CARD_SUCCESS_MATCH, NULL, selecedCard.get(), outer);
                }
                else
                {
                    selecedCard.get()->status = GAME_STATUS::NORMAL;
                    extraCard.get()->status = Game_obj_status::PICKED;
                    outer->selected.push_back(extraCard);
                }
            }
            else
            {
                selecedCard.get()->status = GAME_STATUS::NORMAL;
                extraCard.get()->status = Game_obj_status::PICKED;
                outer->selected.push_back(extraCard);
            }
        }
    }
    else if (msg.extraInfo && (cardInfo = dynamic_cast<CardInfo *>(msg.extraInfo)) && cardInfo->nodeType == LinkANodeType::CARD)
    {
        std::shared_ptr<Card> extraCard = outer->findCardPtrByInfo(cardInfo);

        extraCard.get()->status = Game_obj_status::PICKED;
        outer->selected.push_back(extraCard);
    }
    return true;
}

void Board::dispose()
{
    for (auto it = ptrMapping.begin(); it != ptrMapping.end(); it++)
    {
        it->second.reset();
    }
    ptrMapping.clear();
}