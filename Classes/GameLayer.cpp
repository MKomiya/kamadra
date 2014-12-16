//
//  GameLayer.cpp
//  kamadra
//
//  Created by S_Wyvern on 2014/10/10.
//
//

#include "GameLayer.h"

#define BALL_NUM_X 6
#define BALL_NUM_Y 5

USING_NS_CC;

GameLayer::GameLayer()
: _movingBall(nullptr)
, _movedBall(false)
{
    std::random_device device;
    _engine = std::default_random_engine(device());
    _distForBall = std::discrete_distribution<int>{20, 20, 20, 20, 20, 10};
}

Scene* GameLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = GameLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameLayer::init()
{
    if (!Layer::init())
        return false;
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(_swallowsTouches);
    touchListener->onTouchBegan     = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    touchListener->onTouchMoved     = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    touchListener->onTouchEnded     = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    initBackground();
    initBalls();
    
    return true;
}

void GameLayer::initBackground()
{
    auto bgForPuzzle = Sprite::create("Background2.png");
    bgForPuzzle->setAnchorPoint(Point::ZERO);
    bgForPuzzle->setPosition(Point::ZERO);
    addChild(bgForPuzzle, ZOrder::BgForPuzzle);
}

void GameLayer::initBalls()
{
    for (int x = 1; x <= BALL_NUM_X; ++x) {
        for (int y = 1; y <= BALL_NUM_Y; ++y) {
            newBalls(BallSprite::PositionIndex(x, y));
        }
    }
}

BallSprite* GameLayer::newBalls(BallSprite::PositionIndex positionIndex)
{
    int currentTag = BallSprite::generateTag(positionIndex);
    
    int ballType;
    while(true) {
        ballType = _distForBall(_engine);
        
        auto ballX1Tag = currentTag - 10;
        auto ballX2Tag = currentTag - 20;
        auto ballX1 = (BallSprite*)(getChildByTag(ballX1Tag));
        auto ballX2 = (BallSprite*)(getChildByTag(ballX2Tag));
        
        if (!(ballX1 && ballType == (int)ballX1->getBallType()) ||
            !(ballX2 && ballType == (int)ballX2->getBallType()))
        {
            auto ballY1Tag = currentTag - 1;
            auto ballY2Tag = currentTag - 2;
            auto ballY1 = (BallSprite*)(getChildByTag(ballY1Tag));
            auto ballY2 = (BallSprite*)(getChildByTag(ballY2Tag));
            
            if (!(ballY1 && ballType == (int)ballY1->getBallType()) ||
                !(ballY2 && ballType == (int)ballY2->getBallType()))
            {
                break;
            }
        }
    }
    
    auto ball = BallSprite::create((BallSprite::BallType)ballType, true);
    ball->setPositionIndexAndChangePosition(positionIndex);
    addChild(ball, ZOrder::Ball);
    
    return ball;
}

bool GameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    _movedBall = false;
    _movingBall = getTouchBall(touch->getLocation());
    
    if (_movingBall) {
        return true;
    }
    
    return false;
}
