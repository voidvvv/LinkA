#ifndef __BOARD_H__
#define __BOARD_H__
#include "GameObject.h"
#include "Texture.h"
#include "Game.h"
#include "game_obj/Card.h"
#include "GameEvent.h"
#include "LinkAFinder.h"
#include "AStarPathFinder.hpp"
#include <memory>
#include <map>

class Board : public GameObject
{
public:
    class BaseBoard_CardRecipient : public _Recipient
    {
    public:
        Board *outer;
        virtual bool handleMessage(_LinkAMessage &msg);
    };

private:
    // std::map<void*,std::shared_ptr<Card>> ptrMapping;
    BaseBoard_CardRecipient *main_recipient;

public:
    AStarPathFinder<Card> *pathFinder;
    LinkCardAGraph *graph;

    std::vector<Card *> objs;
    std::vector<Card *> selected;

    std::vector<Card *> linkAPath;
    bool showPath = false;

    int row = 8;
    int column = 8;

    glm::vec3 cardsOrigin;
    float cardGapx;
    float cardGapy;
    float cardWidth;
    float cardHeight;
    Texture *ground;

    virtual void create() override;
    virtual void render(Camera *) override;
    virtual void update(float delta) override;
    virtual void onEvent(LinkA_Event &__event) override;
    virtual void updateLayout();
    // virtual std::shared_ptr<Card> findCardPtrByInfo(CardInfo *ci);
    void dispose();
};

#endif // __BOARD_H__