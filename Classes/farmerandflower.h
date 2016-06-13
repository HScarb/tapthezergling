#ifndef __FARMERANDFLOWER_H__
#define __FARMERANDFLOWER_H__
#pragma once
#include "cocos2d.h"

class farmerandflower :public cocos2d::Sprite
{
public:
	typedef enum
	{
		NONE = 0,
		SCV,
		Marine,
		Marauder,
		Drone,
		Zergling,
		Overlord,
		Roach,
		Probe,
		Zealot,
		Stalker		// 10
	}UnitType;

	static farmerandflower * createByType(int type = NONE);
	bool initByType(int type);

	void eatAnimation();
	void tapped();
	CC_SYNTHESIZE(int, m_colorType, ColorType);


};
#endif