//
//  MoveLeft.h
//  FlappyBird
//
//  Created by Doan Anh Tai on 2/22/14.
//
//

#ifndef __FlappyBird__MoveLeft__
#define __FlappyBird__MoveLeft__

#include <cocos2d.h>

using namespace cocos2d;

class MoveLeft : public Component
{
public:
    MoveLeft(float w);
    
private:
    float w;
    virtual void onEnter();
    virtual void update(float delta);
    
    void actionMove();
    
};

#endif /* defined(__FlappyBird__MoveLeft__) */
