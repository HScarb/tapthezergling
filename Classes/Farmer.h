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
		SCV = 1,		// ����ũ��
		DRONE = 2,		// ����ũ��
		PROBE = 3		// ����ũ��
	};
	static Farmer * FarmerAppear(int type = 0);
	bool init(int appear);
	void tapped();
	CC_SYNTHESIZE(int, m_appear, ColorType);
};