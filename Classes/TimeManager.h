// TimeManager.h
#pragma once
#include "cocos2d.h"

class TimeManager : public cocos2d::Ref
{
public:
	static TimeManager * getInstance();
	virtual bool init();

	void addTime(float t);			// ����ʱ��
	void reduceTime(float t);		// ����ʱ��
private:
	static TimeManager * m_timeManager;
	
	CC_SYNTHESIZE(float, m_time, Time);
};
