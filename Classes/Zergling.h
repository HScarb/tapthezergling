// Zergling.h
#pragma once
#include "cocos2d.h"
#include "FilterSprite.h"

class Zergling : public FilterSprite
{
public:
	enum ZerglingColor
	{
		NONE = 0,
		RED = 1,
		ORANGE,
		YELLOW,
		GREEN,
		CYAN,
		BLUE,
		PURPLE
	};

	static Zergling * createByColor(ZerglingColor color = NONE);
	bool init(int color);

	void eatAnimation();
	void tapped();			// 被点击以后消失
	CC_SYNTHESIZE(int, m_colorType, ColorType);
};