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
    
    void initBackground();
    void initBalls();
    BallSprite* newBalls(BallSprite::PositionIndex positionIndex);
    
public:
    GameLayer();
    virtual bool init();
    CREATE_FUNC(GameLayer);
    static cocos2d::Scene* createScene();
};

#endif /* defined(__kamadra__GameLayer__) */
