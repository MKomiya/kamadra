#ifndef __BALL_SPRITE__
#define __BALL_SPRITE__

#include <cocos2d.h>

#define BALL_SIZE 106
#define ONE_ACTION_TIME 0.2

class BallSprite : public cocos2d::Sprite
{
public:
    enum class BallType
    {
        Blue, Red, Green, Yellow, Purple, Pink,
    };
    
    struct PositionIndex
    {
        PositionIndex()
        {
            x = y = 0;
        }
        PositionIndex(int _x, int _y)
        {
            x = _x;
            y = _y;

        }
        int x, y;
    };
    
    BallSprite();
    static BallSprite* create(BallType type, bool visible);
    virtual bool init(BallType type, bool visible);
    
    CC_SYNTHESIZE(int, _removedNo, RemovedNo);
    CC_SYNTHESIZE(bool, _checkedX, CheckedX);
    CC_SYNTHESIZE(bool, _checkedY, CheckedY);
    CC_SYNTHESIZE(int, _fallCount, FallCount);
    CC_SYNTHESIZE_READONLY(BallType, _ballType, BallType);
    CC_PROPERTY(PositionIndex, _positionIndex, PositionIndex);
    
    void setPositionIndexAndChangePosition(PositionIndex positionIndex);
    void resetParams();
    void resetPosition();
    void removingAndFallingAnimation(int maxRemovedNo);
    
    static std::string getBallImageFilePath(BallType type);
    static cocos2d::Point getPositionForPositionIndex(PositionIndex positionIndex);
    static int generateTag(PositionIndex positionIndex);
    
protected:
    void removingAnimation(int maxRemovedNo);
    void fallingAnimation(int maxRemovedNo);
};

#endif
