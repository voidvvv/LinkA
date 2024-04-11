#include <iostream>
#include "LinkAGame.h"
#include "LinkA.h"
#include <locale>
#include "utf8.h"

#include <AL/alut.h>

void sayHu(){
      ALuint helloBuffer, helloSource;
  alutInit (NULL, NULL);
  helloBuffer = alutCreateBufferHelloWorld ();
  alGenSources (1, &helloSource);
  alSourcei (helloSource, AL_BUFFER, helloBuffer);
  alSourcePlay (helloSource);
  alutSleep (1);
  alutExit ();
  return ;
};

int main (){
    sayHu();
// setlocale(LC_ALL, "chs");
// setlocale(LC_ALL, "C");
    std::cout << "游戏开始" << std::endl;
    Game* __game = new LinkAGame(); 
    start(__game);
    std::cout << "游戏结束" << std::endl;
    std::cin.get();
};