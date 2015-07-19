

#ifndef __FlappyBird__Collision__
#define __FlappyBird__Collision__

#include <cocos2d.h>
#include "Bird.h"

using namespace cocos2d;

class Collision : public Component
{
public:
    Collision(Bird* bird, bool getScore);
    
private:
    Node* parent;
    Bird* bird;
    bool getScore;
    
    virtual void update(float delta);
    
    bool isCollision();
    Point getWorldPosition();
};

#endif /* defined(__FlappyBird__Collision__) */
