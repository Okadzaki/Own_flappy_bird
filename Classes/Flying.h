
#ifndef __FlappyBird__Flying__
#define __FlappyBird__Flying__

#include <cocos2d.h>
#include "Bird.h"

using namespace cocos2d;

class Flying : public Component
{
public:
    Flying();
    
    void actionTap();
    void actionHit();
    void stopAction();
    
private:
    
    Bird* parent;
    virtual void update(float delta);
    
    Action* curAction;
    
    float getDuraDown(Point up, Point down);
    
};

#endif /* defined(__FlappyBird__Flying__) */
