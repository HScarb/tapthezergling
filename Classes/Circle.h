#ifndef __CIRCLE_H__
#define __CIRCLE_H__
#pragma once
#include "cocos2d.h"
#include "FilterSprite.h"

class Circle : public FilterSprite
{
public:
	enum CircleType
	{
		NONE = 0,
		RED = 1,
		ORANGE,
		YELLOW,
		GREEN,
		g1,
		g2,
		g3,
		g4
	};

	static Circle * createByColor(int color = NONE);
	bool init(int color);

private:
	CC_SYNTHESIZE(int, m_colorType, ColorType);
	cocos2d::Sprite * m_circle_sprite;
};
#endif
