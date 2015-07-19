
#include "MoveLoop.h"
#include "config.h"
#include "HelloWorldScene.h"

MoveLoop::MoveLoop()
{
    setName("MoveLoop");
    
}

void MoveLoop::onEnter()
{
    actionMove();
}

void MoveLoop::update(float delta)
{
    Node* parent = (Node*)getOwner();
    if (parent == NULL) return;
    
    if ( ((HelloWorld*)parent->getParent())->GameOver )
    {
        parent->stopAllActions();
    }
}

void MoveLoop::actionMove()
{
    Node* parent = (Node*)getOwner();
    if (parent == NULL) return;
    
    float w = parent->boundingBox().size.width / kLandParts;
    MoveBy* moveleft = MoveBy::create(kMoveLeftDura, Point(-w, 0));
    MoveBy* moveright = MoveBy::create(0, Point(w, 0));
    
    RepeatForever* repeat = RepeatForever::create(Sequence::create(moveleft, moveright, NULL));
    
    parent->runAction(repeat);
    
}
