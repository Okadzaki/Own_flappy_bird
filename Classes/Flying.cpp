

#include "Flying.h"
#include "config.h"

Flying::Flying()
{
    setName("Flying");
    curAction = NULL;
    
}

void Flying::update(float delta)
{
    parent = (Bird*)getOwner();
    if (parent == NULL) return;
    
    if (parent->status == isDie)
    {
        return;
    }
    else if (parent->status == isTap)
    {
        parent->status = isIdle;
        actionTap();
    }
    else if (parent->status == isHit)
    {
        parent->status = isDie;
        actionHit();
    }
}

void Flying::actionTap()
{
    stopAction();
    
    Point uppos = parent->getPosition();
    uppos.y += kJumpHeight;
    
    Point downpos = Point(uppos.x, kLandHeight);
    float duraDown = getDuraDown(uppos, downpos);
    
    MoveTo* moveup = MoveTo::create(kJumpDura, uppos);
    RotateTo* faceup = RotateTo::create(kJumpDura, -30);
    Spawn* fly = Spawn::create(faceup, EaseSineOut::create(moveup), NULL);
    
    
    MoveTo* movedown = MoveTo::create(duraDown, downpos);
    RotateTo* facedown = RotateTo::create(kJumpDura*2, 90);
    Spawn* fall = Spawn::create(facedown, EaseSineIn::create(movedown), NULL);
    
    Sequence* tap = Sequence::create(fly, fall, NULL);
    
    curAction = tap;
    parent->runAction(tap);
    
}

float Flying::getDuraDown(Point up, Point down)
{
    
    float dy = up.y - down.y;
    float duraDown;
    
    if (dy <= kJumpHeight) duraDown = kJumpDura * 1/2;
    {
        duraDown = dy * (kJumpDura * 1/2) / kJumpHeight;
    }
    
    return duraDown;
}

void Flying::actionHit()
{
    Point upPos = parent->getPosition();
    parent->stopAllActions();
    
    Point downPos = Point(upPos.x, kLandHeight);
    float duraDown = getDuraDown(upPos, downPos) * 1/2;
    
    MoveTo* movedown = MoveTo::create(duraDown, downPos);
    RotateTo* facedown = RotateTo::create(duraDown, 90);
    Spawn* fall = Spawn::create(facedown, EaseSineIn::create(movedown), NULL);
    
    curAction = fall;
    parent->runAction(fall);
}

void Flying::stopAction()
{
    if (curAction != NULL)
    {
        parent->stopAction(curAction);
        curAction = NULL;
    }
}



