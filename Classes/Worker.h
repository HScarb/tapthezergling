//Worker.h
#pragma once
#include"cocos2d.h"

class Worker :public cocos2d::Sprite
{
public:
	enum Workertype
	{
		NONE = 0,
		SCV = 1,		// ����ũ��
		DRONE = 2,		// ����ũ��
		PROBE = 3		// ����ũ��
	};
	static Worker * Workertype(int type = 0);
	bool init(int type);
	void tapped();
	CC_SYNTHESIZE(int, m_appear, ColorType);

};