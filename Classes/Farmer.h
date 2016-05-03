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
		APPEAR = 1,
	};
	static Farmer * FarmerAppear(Farmerappear appear = NONE);
	bool init(int appear);
	void tapped();
	CC_SYNTHESIZE(int, m_appear, ColorType);
};