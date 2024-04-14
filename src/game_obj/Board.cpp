#include "game_obj/Board.h"
#include "LinkALog.h"

extern Game *game;
void printPath(std::vector<Card *> path)
{
    std::cout << "----" << std::endl;
    for (Card *c : path)
    {
        std::cout << c->center.x << " - " << c->center.y << std::endl;
    }

    std::cout << "----" << std::endl;
};

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
    int scale = 1;
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
        if (x_pos == y_pos)
        {
            tst->nodeType = LinkANodeType::OBSTACLE;
        }
        tst->create();
        // std::shared_ptr<Card> ptr(tst);
        // ptrMapping[tst] = ptr;
        objs.push_back(tst);
        this->graph->nodeVector.push_back(tst);
    }

    this->updateLayout();
    pathFinder->init(graph);
    main_recipient = new BaseBoard_CardRecipient();
    main_recipient->outer = this;
    events->registListerner(_CARD_SELECTED, main_recipient);
}

void Board::render(Camera *camera)
{
    game->getSpriteRender()->DrawSprite(ground, position, camera->getProjectionMatrix(), camera->getViewMatrix(), size);

    for (Card* objPtr : objs)
    {
        objPtr->render(camera);
    }

    // render path
    if (showPath && linkAPath.size() >= 2)
    {

        for (int i = 0; i < linkAPath.size() - 1; i++)
        {
            glm::vec2 pos1 = linkAPath[i]->center;
            glm::vec2 pos2 = linkAPath[i + 1]->center;
            game->getBasicRender()->drawLine(pos1, pos2, camera, glm::vec3(1.0f, 0.f, 0.f), glm::vec3(1.0f, 0.f, 0.f));
        }
    }
}

void Board::update(float delta)
{
    for (auto it = objs.begin(); it != objs.end();)
    {
        Card* objPtr = (*it);
        if (objPtr->delFlag)
        {
            // it = objs.erase(it);
            // objPtr.reset();
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

    for (Card* objPtr : objs)
    {
        if (!event.s)
        {
            break;
        }
        objPtr->onEvent(event);
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
        Card* objPtr = objs[i];
        int c_col = i % column;
        int c_row = i / column;

        objPtr->position.x = cardGapx * (c_col + 1) + cardWidth * c_col + cardsOrigin.x;
        objPtr->position.y = cardGapy * (c_row + 1) + c_row * cardHeight + cardsOrigin.y;

        objPtr->size.x = cardWidth;
        objPtr->size.y = cardHeight;

        // 啊 这
        objPtr->center.x = objPtr->position.x + cardWidth / 2;
        objPtr->center.y = objPtr->position.y + cardHeight / 2;
        if (c_col + 1 < column)
        {
            addConnection(objPtr, objs[i + 1]);
        }
        if (c_col - 1 >= 0)
        {
            addConnection(objPtr, objs[i - 1]);
        }
        if (c_row + 1 < row)
        {
            addConnection(objPtr, objs[i + column]);
        }
        if (c_row - 1 >= 0)
        {
            addConnection(objPtr, objs[i - column]);
        }
    }
}



bool Board::BaseBoard_CardRecipient::handleMessage(_LinkAMessage &msg)
{
    if (msg.messageType != _CARD_SELECTED)
    {
        return false;
    }
    outer->showPath = false;
    Card *cardInfo = NULL;
    bool f = msg.extraInfo && (cardInfo = dynamic_cast<Card *>(msg.extraInfo)) && cardInfo->nodeType == LinkANodeType::CARD;
    if (f && outer->selected.size() > 0)
    {
        Card* selecedCard = outer->selected[0];
        outer->selected.erase(std::remove(outer->selected.begin(), outer->selected.end(), selecedCard), outer->selected.end());

        if (msg.extraInfo && (cardInfo = dynamic_cast<Card *>(msg.extraInfo)) && cardInfo->nodeType == LinkANodeType::CARD)
        {
            Card* extraCard = cardInfo;
            if (extraCard != selecedCard && selecedCard->compare_id == extraCard->compare_id)
            {
                outer->linkAPath.clear();
                // check type success
                // std::vector<Card *> outPath;
                bool b = outer->pathFinder->searchNodePath(extraCard, selecedCard, Game_Heuristic, Game_ShouldStop, outer->linkAPath);
                std::cout << "A: X - [" << extraCard->x << "]  Y - [" << extraCard->y << "]  B: x - [" << selecedCard->x << "]   y- [" << selecedCard->y << "] reseult: " << b << std::endl;

                if (b)
                {
                    std::cout << "outer->linkAPath size: " << outer->linkAPath.size() << std::endl;
                    printPath(outer->linkAPath);
                    outer->showPath = true;
                    events->sendMessaage(_CARD_SUCCESS_MATCH, NULL, extraCard, outer);
                    events->sendMessaage(_CARD_SUCCESS_MATCH, NULL, selecedCard, outer);

                    events->sendMessaage(_CARD_SUCCESS_MATCH_GLOBAL, NULL, NULL, outer);
                }
                else
                {
                    selecedCard->status = GAME_STATUS::NORMAL;
                    extraCard->status = Game_obj_status::PICKED;
                    outer->selected.push_back(extraCard);
                }
            }
            else
            {
                selecedCard->status = GAME_STATUS::NORMAL;
                extraCard->status = Game_obj_status::PICKED;
                outer->selected.push_back(extraCard);
            }
        }
    }
    else if (msg.extraInfo && (cardInfo = dynamic_cast<Card *>(msg.extraInfo)) && cardInfo->nodeType == LinkANodeType::CARD)
    {
        Card* extraCard = cardInfo;

        extraCard->status = Game_obj_status::PICKED;
        outer->selected.push_back(extraCard);
    }
    else
    {
        // obstacle click
    }
    return true;
}

void Board::dispose()
{
    for (auto it = objs.begin(); it != objs.end(); it++)
    {
        (*it)->dispose();
        delete (*it);
    }
    objs.clear();
    selected.clear();
    linkAPath.clear();
    delete graph;
    delete pathFinder;
    
    events->removeListerner(main_recipient);
    delete main_recipient;
}