// TimeManager.h
#pragma once
#include "cocos2d.h"

class TimeManager : public cocos2d::Node
{
public:
	static TimeManager * getInstance();
	virtual bool init() override;

	void addTime(float t);			// ����ʱ��
	void reduceTime(float t);		// ����ʱ��
	void startCountDown();
	void pauseCountDown();
	void resumeCountDown();			// ����ͣ�лָ�

	bool isCountingDown();			// �����Ƿ��ڵ���
	
	virtual void update(float dt) override;
private:
	static TimeManager * m_timeManager;
	bool m_isCountingDown;
	
	CC_SYNTHESIZE(float, m_preTime, PreTime);
	CC_SYNTHESIZE(float, m_time, Time);
	CC_SYNTHESIZE(bool, m_isTollgateBegin, isTollgateBegin);		// �ؿ��Ƿ��Ѿ���ʼ(��ͣҪ�õ�)
};
