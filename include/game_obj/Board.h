#ifndef __BOARD_H__
#define __BOARD_H__
#include "GameObject.h"
#include "Texture.h"
#include "Game.h"


class Board : public GameObject
{
public:
    Texture* ground;
    glm::vec2 position;
    glm::vec2 size;

    virtual void create() override;
    virtual render(Camera *) override;
    virtual update(float delta) override;
    virtual void onEvent(LinkA_Event& __event) override;
};
#endif // __BOARD_H__