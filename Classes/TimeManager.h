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
	void resumeCountDown();			// 从暂停中恢复

	bool isCountingDown();			// 返回是否在倒数
	
	virtual void update(float dt) override;
private:
	static TimeManager * m_timeManager;
	bool m_isCountingDown;
	
	CC_SYNTHESIZE(float, m_preTime, PreTime);
	CC_SYNTHESIZE(float, m_time, Time);
	CC_SYNTHESIZE(bool, m_isTollgateBegin, isTollgateBegin);		// 关卡是否已经开始(暂停要用到)
};
