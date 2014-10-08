#ifndef __BALL_SPRITE__
#define __BALL_SPRITE__

#include <cocos2d.h>

class BallSprite : public cocos::Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(BallSprite);
};

#endif
