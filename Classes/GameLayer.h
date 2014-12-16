//
//  GameLayer.h
//  kamadra
//
//  Created by S_Wyvern on 2014/10/10.
//
//

#ifndef __kamadra__GameLayer__
#define __kamadra__GameLayer__

#include <stdio.h>
#include "cocos2d.h"
#include <random>

#include "BallSprite.h"

class GameLayer : public cocos2d::Layer
{
protected:
    enum class Direction {
        x, y
    };
    enum ZOrder {
        BgForCharacter = 0,
        BgForPuzzle,
        Enemy,
        EnemyHp,
        Char,
        CharHp,
        Ball,
        Level,
        Result,
    };
    
    std::default_random_engine _engine;
    std::discrete_distribution<int> _distForBall;
    BallSprite* _movingBall;
    bool _movedBall;
    
    void initBackground();
    void initBalls();
    BallSprite* newBalls(BallSprite::PositionIndex positionIndex);
    BallSprite* getTouchBall(cocos2d::Point touchPos, BallSprite::PositionIndex withoutPosIndex = BallSprite::PositionIndex());
    void movedBall();
    
public:
    GameLayer();
    virtual bool init();
    CREATE_FUNC(GameLayer);
    static cocos2d::Scene* createScene();
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
};

#endif /* defined(__kamadra__GameLayer__) */
