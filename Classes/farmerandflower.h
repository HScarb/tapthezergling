#ifndef __FARMERANDFLOWER_H__
#define __FARMERANDFLOWER_H__
#pragma once
#include "cocos2d.h"
#include "FilterSprite.h"

class Farmerandflower :public FilterSprite
{
public:
	enum Color
	{
		NONE = 0,
		RED = 1,
		YELLOW,
		BLUE,
		GREEN,
		PINK,
		BLCAK,
		PURPLE
	};

	static Farmerandflower * farmerandflowerAppear(int color = NONE);
	bool init(int color);

	void tapped();
	CC_SYNTHESIZE(int, m_colorType, ColorType);


};
#endif