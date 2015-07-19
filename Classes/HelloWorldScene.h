#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Bird.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(HelloWorld);
    
    void addPipe();
    bool GameOver;
    void updateUiScore();
    
    void playSound(std::string name);

private:
    
private:
    
    cocos2d::Size s;
    cocos2d::Sprite* land;
    Bird* bird;
    
    cocos2d::ParallaxNode* layerMoveLeft;
    
    cocos2d::Label* lbscore;
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event) override;
    
    void addBackground();
    void addLand();
    void addBird();
    void addLayerMoveLeft();
    void addLabelScore();
    
    void resetGame();

};

#endif // __HELLOWORLD_SCENE_H__
