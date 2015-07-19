#include "HelloWorldScene.h"
#include "config.h"
#include "audio/include/SimpleAudioEngine.h"
#include "MoveLoop.h"
#include "Flying.h"
#include "MoveLeft.h"
#include "AddPipe.h"
#include "Collision.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool HelloWorld::init()
{
    //////////////////////////////
    if ( !Layer::init() )
    {
        return false;
    }

    _eventDispatcher->removeAllEventListeners();

   auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    //--------------------------------------------------------------------------
    
    s = Director::getInstance()->getWinSize();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("flappy.plist");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SoundTap);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SoundHit);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SoundPoint);

    bird = NULL;
    resetGame();
    this->addComponent(new AddPipe());
    
    return true;
}

void HelloWorld::resetGame()
{
    this->unscheduleUpdate();
    if (bird != NULL) bird->unscheduleUpdate();
    
    this->removeAllChildrenWithCleanup(true);
    
    GameOver = false;
    
    addBackground();
    addLand();
    addBird();
    addLayerMoveLeft();
    addLabelScore();
    
    this->scheduleUpdate();
    bird->scheduleUpdate();
    
}

void HelloWorld::addLabelScore()
{
    char strp[100] = {0};
    sprintf(strp, "%d", bird->score);
    lbscore = Label::createWithTTF(strp, "fonts/arial.ttf", 30);
    lbscore->setZOrder((int)getChildrenCount()); //font of all
    lbscore->setPosition(s.width/2, s.height - 20);
    
    this->addChild(lbscore);
}

void HelloWorld::updateUiScore()
{
    char strp[100] = {0};
    sprintf(strp, "%d", bird->score);
    lbscore->setString(strp);
}

void HelloWorld::addBackground()
{
    Sprite* bg = Sprite::createWithSpriteFrameName("background.png");
    bg->setPosition(s.width/2, s.height/2);
    this->addChild(bg);
    
}

void HelloWorld::addLand()
{
    land = Sprite::createWithSpriteFrameName("land.png");
    land->setZOrder(2);
    land->setAnchorPoint(Point(0, 0.5));
    land->setPosition(0, land->boundingBox().size.height/2 - 4);
    
   land->addComponent(new MoveLoop());
    
    this->addChild(land);
    
}

void HelloWorld::addBird()
{
    bird = new Bird();
    bird->setZOrder(1000);
    bird->setPosition(s.width/2, s.height/2);
    
    bird->addComponent(new Flying());
    
    this->addChild(bird);
}

void HelloWorld::addLayerMoveLeft()
{
    layerMoveLeft = ParallaxNode::create();
    layerMoveLeft->addComponent(new MoveLeft(land->boundingBox().size.width) );
    this->addChild(layerMoveLeft);
}

void HelloWorld::addPipe()
{

    int r = rand();
    r = r%5;
    float dy = r * 10; //random 0, 10, 20, 30, 40

    r = rand();
    r = r%2;
    if (r==0) dy = -dy;
    
    
    Sprite* pipe1 = Sprite::createWithSpriteFrameName("pipe1.png");
    Point pos = Point(s.width + pipe1->boundingBox().size.width/2,
                      s.height/2 + pipe1->boundingBox().size.height/2
                      + kHoleBetweenPipe/2 + kLandHeight/2 + dy
                      );
    Point pospipe1 = (layerMoveLeft->convertToNodeSpace(pos));
    
    Sprite* pipe2 = Sprite::createWithSpriteFrameName("pipe2.png");
    pos.y = s.height/2 - pipe2->boundingBox().size.height/2 - kHoleBetweenPipe + kLandHeight/2 + dy;
    Point pospipe2 = (layerMoveLeft->convertToNodeSpace(pos));
    

    int zOrder = land->getZOrder() - 1;
    
    pipe1->addComponent(new Collision(bird, true));
    pipe2->addComponent(new Collision(bird, false));
    
    layerMoveLeft->addChild(pipe1, zOrder, Point(1, 0), pospipe1);
    layerMoveLeft->addChild(pipe2, zOrder, Point(1, 0), pospipe2);
    
    pipe1->scheduleUpdate();
    pipe2->scheduleUpdate();
    
}

//-----------------------------
bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
    if (GameOver)
    {
        resetGame();
    }
    else
    {
        bird->tapMe();
    }
    
    return true;
}



void HelloWorld::playSound(std::string name)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(name.c_str());
}


