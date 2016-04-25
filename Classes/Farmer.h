//Frmer.h
#pragma once
#include "cocos2d.h"
#include "FilterSprite.h"
using namespace cocos2d;

class Farmer :public FilterSprite
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