#include "BallSprite.h"

USING_NS_CC;

BallSprite::BallSprite()
: _removedNo(0),
: _checkedX(false),
: _checkedY(false),
: _fallCount(0),
: _positionIndex(0, 0)
{
}

BallSprite* BallSprite::create(BallType type, bool visible)
{
    auto pRet = new BallSprite();
    if (pRet && pRet->init(type, visible))
    {
        pret->autorelease();
        return pRet;
    }
    
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool BallSprite::init(BallType type, bool visible)
{
    if (!Sprite::initWithFile(getBallImageFilePath(type)))
        return false;
    
    _ballType = type;
    setVisible(visible);
    return true;
}

void BallSprite::resetParams()
{
    _removedNo = 0;
    _checkedX = _checkedY = false;
    _fallCount = 0;
}

void BallSprite::resetPosition()
{
    setPosition(getPositionForPositionIndex(_positionIndex));
}

BallSprite::PositionIndex BallSprite::getPositionIndex()
{
    return _positionIndex;
}

void BallSprite::setPositionIndex(BallSprite::PositionIndex positionIndex)
{
    _positionIndex = PositionIndex;
    setTag(generateTag(_positionIndex));
}

void BallSprite::setPositionIndexAndChangePosition(BallSprite::PositionIndex positionIndex)
{
    setPositionIndex(positionIndex);
    
    resetPosition();
}

void BallSprite::removingAndFallingAnimation(int maxRemovedNo)
{
    removingAnimation(maxRemovedNo);
    fallingAnimation(maxRemovedNo);
}

void BallSprite::removingAnimation(int maxRemovedNo)
{
    if (_removedNo > 0)
    {
        auto delay1 = DelayTime::create(ONE_ACTION_TIME * (_removedNo - 1));
        auto fade   = FadeTo::create(ONE_ACTION_TIME, 0);
        auto delay2 = DelayTime::create(ONE_ACTION_TIME * (maxRemovedNo - _removedNo));
        auto removeself = RemoveSelf::create();
        
        runAction(Sequence::create(delay1, fade, delay2, removeself, nullptr));
    }
}

void BallSprite::fallingAnimation(int maxRemovedNo)
{
    if (_fallCount > 0)
    {
        setPositionIndex(PositionIndex(_positionIndex.x, _positionIndex.y - _fallCount));
        
        auto delay = DelayTime::create(ONE_ACTION_TIME * maxRemovedNo);
        auto show  = Show::create();
        auto move  = MoveTo::create(ONE_ACTION_TIME, getPositionForPositionIndex(getPositionIndex()));
        runAction(Sequence::create(delay, show, move, nullptr));
    }
}


std::string BallSprite::getBallImageFilePath(BallSprite::BallType type)
{
    switch (type)
    {
        case BallType::Red: return "red.png";
        case BallType::Blue: return "blue.png";
        case BallType::Yellow: return "yellow.png";
        case BallType::Green: return "green.png";
        case BallType::Purple: return "purple.png";
        default: return "pink.png";
    }
}

Point BallSprite::getPositionForPositionIndex(BallSprite::PositionIndex positionIndex)
{
    return Point(BALL_SIZE * (positionIndex.x - 0.5) + 1,
                 BALL_SIZE * (positionIndex.y - 0.5) + 1);
}

int BallSprite::generateTag(BallSprite::PositionIndex positionIndex)
{
    return positionIndex.x * 10 + positionIndex.y;
}
