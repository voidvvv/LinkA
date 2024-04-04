#include "ObjUtil.h"

bool contain(GameObject * objPtr, LinkA_Event & e)
{
    glm::vec2 position = objPtr->position;
    glm::vec2 size = objPtr->size;
    return (e.pos.x >= position.x && e.pos.x <= (position.x + size.x) && e.pos.y >= position.y && e.pos.y <= (position.y + size.y));
}