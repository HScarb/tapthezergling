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

	bool isCountingDown();			// 返回是否在倒数

	virtual void update(float dt) override;

	//卡片管理器时间管理
	void reduceCardTime(float t);
	void startCardTimeCountDown();
	bool isCardTimeCountingDowm();

private:
	static TimeManager * m_timeManager;
	bool m_isCountingDown;
	
	CC_SYNTHESIZE(float, m_preTime, PreTime);
	CC_SYNTHESIZE(float, m_time, Time);

private:
	static TimeManager * m_cardtimeManager;
	bool m_iscardTimeCountingDown;

	CC_SYNTHESIZE(float, m_cardtime, CardTime);
};