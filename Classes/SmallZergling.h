// SmallZergling.h
#pragma once
#include "cocos2d.h"

class SmallZergling : public cocos2d::Sprite
{
public:
	CREATE_FUNC(SmallZergling);
	virtual bool init() override;

	void idle();
	void run();

	// actions
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _idleAction, IdleAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _runAction, RunAction);

private:

};
