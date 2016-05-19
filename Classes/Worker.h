//Worker.h
#pragma once
#include"cocos2d.h"

class Worker :public cocos2d::Sprite
{
public:
	enum Workertype
	{
		NONE = 0,
		SCV = 1,		// 人族农民
		DRONE = 2,		// 虫族农民
		PROBE = 3		// 神族农民
	};
	static Worker * Workertype(int type = 0);
	bool init(int type);
	void tapped();
	CC_SYNTHESIZE(int, m_appear, ColorType);

};