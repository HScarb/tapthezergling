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

	bool isCountingDown();			// �����Ƿ��ڵ���

	virtual void update(float dt) override;

	//��Ƭ������ʱ�����
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