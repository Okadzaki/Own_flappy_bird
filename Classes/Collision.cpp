

#include "Collision.h"

Collision::Collision(Bird* bird, bool getScore)
{
    setName("Collision");
    
    this->bird = bird;
    this->getScore = getScore;
}

void Collision::update(float delta)
{
    parent = (Node*)getOwner();
    if (parent == NULL) return;
    
    if (bird->status == isDie) return;
    
    if (getScore)
    {
        if (getWorldPosition().x <= bird->getPosition().x)
        {
            getScore = false;
            bird->updateScore();
        }
    }
    
    if (isCollision())
    {
        bird->hitMe();
    }
}

bool Collision::isCollision()
{
    Size spipe = parent->boundingBox().size;
    Point ppipe = getWorldPosition();
    
    Size sbird = bird->boundingBox().size;
    Point pbird = bird->getPosition();
    
    float d = 6;
    
    float maxx1 = ppipe.x + spipe.width/2 - d;
    float minx1 = ppipe.x - spipe.width/2 + d;
    float maxy1 = ppipe.y + spipe.height/2 - d;
    float miny1 = ppipe.y - spipe.height/2 + d;
    
    float maxx2 = pbird.x + sbird.width/2 - d;
    float minx2 = pbird.x - sbird.width/2 + d;
    float maxy2 = pbird.y + sbird.height/2 - d;
    float miny2 = pbird.y - sbird.height/2 + d;
    
    return !(maxx1 < minx2 ||
             maxx2 < minx1 ||
             maxy1 < miny2 ||
             maxy2 < miny1);
    
}

Point Collision::getWorldPosition()
{
    return ((ParallaxNode*)parent->getParent())->convertToWorldSpace(parent->getPosition());
}

