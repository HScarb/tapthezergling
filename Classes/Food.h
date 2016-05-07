#ifndef __FOOD_H__
#define __FOOD_H__
#pragma once
#include "cocos2d.h"
#include "FilterSprite.h"

class Food :public FilterSprite
{
public:
	enum Foodtype
	{
		NONE = 0,
		RED = 1,
		YELLOW,
		BLUE
	};

	static Food * createByType(Foodtype type = NONE);
	bool init(int color);

	void eatAnimation();
	void tapped();
	CC_SYNTHESIZE(int, m_colorType, ColorType);

};
#endif