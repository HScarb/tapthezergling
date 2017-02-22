// TimeManager.h
#pragma once
#include <ctime>					// for tm & time_t
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

	//��Ƭ������ʱ�����
	void reduceCardTime(float t);
	void startCardTimeCountDown();
	bool isCardTimeCountingDowm();
	void pauseCardTimeCountingDown();

	__int64 getCurrentDateTime();		// ��ȡ�����ʱ��

private:
	static TimeManager * m_timeManager;
	bool m_isCountingDown;

	CC_SYNTHESIZE(float, m_preTime, PreTime);
	CC_SYNTHESIZE(float, m_time, Time);
	CC_SYNTHESIZE(bool, m_isTollgateBegin, isTollgateBegin);		// �ؿ��Ƿ��Ѿ���ʼ(��ͣҪ�õ�)

private:
	bool m_iscardTimeCountingDown;

	CC_SYNTHESIZE(float, m_cardtime, CardTime);
};
