#ifndef __PICKLEVELSCREEN_H__
#define __PICKLEVELSCREEN_H__

#include "Screen.h"

class PickLevelScreen: public Screen{
public:
    virtual void create() ;
    virtual void render() ;
    virtual void update(float delta) ;
    virtual void dispose() ;
    virtual void sendEvent(LinkA_Event& event) ;
};

#endif // __PICKLEVELSCREEN_H__