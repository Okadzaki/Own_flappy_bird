

#include "Bird.h"
#include "config.h"
#include "HelloWorldScene.h"

Bird::Bird()
{
    initWithSpriteFrameName("bird1.png");
    this->runAction(flying());
    
    status = isIdle;
    score = 0;
    
}

RepeatForever* Bird::flying()
{
    int numframe = 3;
    Vector<SpriteFrame*> animFrames;
    

    char str[100] = {0};
    for(int i = 0; i < numframe; i++)
    {
        sprintf(str, "bird%d.png", i+1);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    

    auto animation = Animation::createWithSpriteFrames(animFrames, 0.05);
    Animate* animate = Animate::create(animation);
    
    return RepeatForever::create(animate);
}

void Bird::tapMe() {

    status = isTap;
    ((HelloWorld*)getParent())->playSound(SoundTap);
    
    
}

void Bird::hitMe()
{
    status = isHit;
    
    ((HelloWorld*)getParent())->GameOver = true;
    ((HelloWorld*)getParent())->playSound(SoundHit);
    
}

void Bird::updateScore()
{
    score ++;
    ((HelloWorld*)getParent())->updateUiScore();
    
    ((HelloWorld*)getParent())->playSound(SoundPoint);
}
