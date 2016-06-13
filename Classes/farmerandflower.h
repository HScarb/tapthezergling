#ifndef __FARMERANDFLOWER_H__
#define __FARMERANDFLOWER_H__
#pragma once
#include "cocos2d.h"
#include "FilterSprite.h"

class farmerandflower :public cocos2d::Sprite
{
public:
	enum FlowerColor
	{
		NONE = 0,
		RED = 1,
		YELLOW = 2,
		BLUE = 3,
		PINK = 4
	};

	static farmerandflower * createByColor(int color = NONE);
	bool init(int color);

	void eatAnimation();
	void tapped();
	CC_SYNTHESIZE(int, m_colorType, ColorType);


};
#endif