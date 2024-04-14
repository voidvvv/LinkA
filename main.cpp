#include <iostream>
#include "LinkAGame.h"
#include "LinkA.h"


int main()
{
    std::cout << "游戏开始" << std::endl;
    Game *__game = new LinkAGame();
    start(__game);
    std::cout << "游戏结束" << std::endl;
    alutExit();
    std::cin.get();
};