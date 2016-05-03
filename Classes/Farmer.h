//Frmer.h
#pragma once
#include "cocos2d.h"
#include "FilterSprite.h"

class Farmer :public cocos2d::Sprite
{
public:
	enum Farmerappear
	{
		NONE = 0,
		SCV = 1,		// 人族农民
		DRONE = 2,		// 虫族农民
		PROBE = 3		// 神族农民
	};
	static Farmer * FarmerAppear(int type = 0);
	bool init(int appear);
	void tapped();
	CC_SYNTHESIZE(int, m_appear, ColorType);
};