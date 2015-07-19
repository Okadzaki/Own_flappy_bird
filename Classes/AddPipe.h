

#ifndef __FlappyBird__AddPipe__
#define __FlappyBird__AddPipe__

#include <cocos2d.h>
#include "HelloWorldScene.h"

using namespace cocos2d;

class AddPipe : public Component
{
public:
    AddPipe();
private:
    
    HelloWorld* parent;
    
    float dura;
    virtual void update(float delta);
};

#endif /* defined(__FlappyBird__AddPipe__) */
