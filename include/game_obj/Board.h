#ifndef __BOARD_H__
#define __BOARD_H__
#include "GameObject.h"
#include "Texture.h"
#include "Game.h"


class Board : public GameObject
{
public:
    Texture* ground;

    virtual void create() override;
    virtual void render(Camera *) override;
    virtual void update(float delta) override;
    virtual void onEvent(LinkA_Event& __event) override;
};
#endif // __BOARD_H__