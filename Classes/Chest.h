//Chest.h
#pragma once
#include "cocos2d.h"
#include "FilterSprite.h"

class Chest : public FilterSprite
{
public:
	enum ChestColor
	{
		NONE = 0,
		BLUE,
		YELLOW
	};

	static Chest * createByColor(ChestColor color = NONE);
	bool init(int color);

	//void tapped();			// 被点击以后消失，出现宝石或者卡片，能量
	CC_SYNTHESIZE(int, m_colorType, ColorType);
};