// SmallZergling.h
#pragma once
#include "cocos2d.h"

class SmallZergling : public cocos2d::Sprite
{
public:
	CREATE_FUNC(SmallZergling);
	virtual bool init() override;

	void runToLeft();
	void runToRight();
private:

};
