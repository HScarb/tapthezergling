// TimeManager.h
#pragma once
#include "cocos2d.h"

class TimeManager : public cocos2d::Node
{
public:
	static TimeManager * getInstance();
	virtual bool init() override;

	void addTime(float t);			// 增加时间
	void reduceTime(float t);		// 减少时间
	void startCountDown();
	void pauseCountDown();
	
	void update(float dt);
private:
	static TimeManager * m_timeManager;
	bool m_isCountingDown;
	
	CC_SYNTHESIZE(float, m_time, Time);
};
