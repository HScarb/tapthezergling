#ifndef __FLOWER_H__
#define __FLOWER_H__
#pragma once
#include "cocos2d.h"
#include "FilterSprite.h"

class Flower :public FilterSprite
{
public:
	typedef enum
	{
		NONE = 0,
		RED = 1,
		YELLOW = 2,
		BLUE = 3,
		PINK = 4
	}FlowerColor;

	static Flower * createByColor(int color = NONE);
	bool init(int color);

	void eatAnimation();
	void tapped();
	CC_SYNTHESIZE(int, m_colorType, ColorType);

	
};
#endif