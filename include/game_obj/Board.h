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
private:
    std::map<void*,std::shared_ptr<Card>> ptrMapping;
public:
    AStarPathFinder<Card>* pathFinder;
    LinkCardAGraph* graph;

    std::vector<std::shared_ptr<Card>> objs;
    std::vector<std::shared_ptr<Card>> selected;

    int row = 8;
    int column = 8;

    glm::vec3 cardsOrigin;
    float cardGapx;
    float cardGapy;
    float cardWidth;
    float cardHeight;
    Texture *ground;

    class BaseBoard_CardRecipient : public _Recipient
    {
    public:
        Board *outer;
        virtual bool handleMessage(_LinkAMessage &msg);
    };
    virtual void create() override;
    virtual void render(Camera *) override;
    virtual void update(float delta) override;
    virtual void onEvent(LinkA_Event &__event) override;
    virtual void updateLayout();
    virtual std::shared_ptr<Card> findCardPtrByInfo(CardInfo *ci);
    void dispose();
};

#endif // __BOARD_H__