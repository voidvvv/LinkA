#ifndef __BOARD_H__
#define __BOARD_H__
#include "GameObject.h"
#include "Texture.h"
#include "Game.h"
#include "game_obj/Card.h"
#include "GameEvent.h"

class Board : public GameObject
{
public:
    std::vector<Card *> objs;
    std::vector<Card *> selected;

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
    void dispose();
};

#endif // __BOARD_H__