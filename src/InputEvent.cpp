#include "InputEvent.h"
#include "miscellaneous.h"
#include <iostream>


void InputEvent::mouseMove(double x, double y){
    this->xpos = static_cast<float>(x);
    this->ypos = static_cast<float>(SCREEN_HEIGH - y);
    
}

void InputEvent::keyEvent( int key, int scancode, int action, int mods){

}

 void InputEvent::mouseButton(int button, int action, int mods) {
    if (action == GLFW_RELEASE){
        std::cout<< "x: " << this->xpos << " Y: " << this->ypos << std::endl;
    }

 }