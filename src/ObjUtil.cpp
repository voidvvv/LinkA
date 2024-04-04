#include "ObjUtil.h"

bool contain(GameObject * objPtr, LinkA_Event & e)
{
    glm::vec2 position = objPtr->position;
    glm::vec2 size = objPtr->size;
    std::cout << e.world_pos.x << " - " << e.world_pos.y << std::endl;
    return (e.world_pos.x >= position.x && e.world_pos.x <= (position.x + size.x) && e.world_pos.y >= position.y && e.world_pos.y <= (position.y + size.y));
}