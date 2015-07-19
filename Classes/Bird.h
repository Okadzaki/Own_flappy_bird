

#ifndef __FlappyBird__Bird__
#define __FlappyBird__Bird__

#include <cocos2d.h>

using namespace cocos2d;

typedef enum {
 
    isTap,
    isDie,
    isHit,
    isIdle,
    
}BirdStatus;

class Bird : public Sprite
{
public:
    Bird();
    
    BirdStatus status;
    int score;
    
    void tapMe();
    void hitMe();
    void updateScore();

private:
    RepeatForever* flying();
    
};


#endif /* defined(__FlappyBird__Bird__) */
