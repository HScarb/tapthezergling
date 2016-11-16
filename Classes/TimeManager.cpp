// TimeManager.cpp
#include "TimeManager.h"
USING_NS_CC;

TimeManager * TimeManager::m_timeManager = nullptr;

TimeManager* TimeManager::getInstance()
{
	if(m_timeManager == nullptr)
	{
		m_timeManager = new TimeManager();
		if(m_timeManager && m_timeManager->init())
		{
			m_timeManager->autorelease();
			m_timeManager->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_timeManager);
			m_timeManager = nullptr;
		}
	}
	return m_timeManager;
}

bool TimeManager::init()
{
	if (!Node::init())
		return false;
	m_iscardTimeCountingDown = false;	//���ÿ�Ƭ����Ϊfalse
	m_isCountingDown = false;		// �������ڵ���Ϊfalse
	m_isTollgateBegin = false;
	this->scheduleUpdate();			// ��ʼ����update����
	

	return true;
}

void TimeManager::addTime(float t)
{
	m_preTime = m_time;
	m_time += t;
}

void TimeManager::reduceTime(float t)
{
	m_preTime = m_time;
	m_time -= t;
}

void TimeManager::startCountDown()
{
	m_isCountingDown = true;
	m_isTollgateBegin = true;		// �ؿ���ʼ����ʱ
	m_preTime = m_time;
}

void TimeManager::pauseCountDown()
{
	m_isCountingDown = false;
}

void TimeManager::resumeCountDown()
{
	// ����ؿ��Ѿ���ʼ���ָ�ʱ��������ʱ������ؿ�û�п�ʼ���޶���
	if(m_isTollgateBegin)
		m_isCountingDown = true;
}

bool TimeManager::isCountingDown()
{
	return m_isCountingDown;
}

void TimeManager::startCardTimeCountDown()
{
	m_iscardTimeCountingDown = true;
}

bool TimeManager::isCardTimeCountingDowm()
{
	return m_iscardTimeCountingDown;
}

void TimeManager::reduceCardTime(float t)
{
	m_cardtime -= t;
}

void TimeManager::update(float dt)
{
	if (m_isCountingDown)		// ������ڵ�������ô������ʱ��
	{
		m_time -= dt;
		if(m_time <= 0.0)
		{
			m_isCountingDown = false;
			m_time = 0;
			_eventDispatcher->dispatchCustomEvent("tollgate_fail"/* , (void*)score */);
		}
	}
	if (m_iscardTimeCountingDown)
	{
		m_cardtime -= dt;
		if (m_cardtime <= 0.0)
		{
			m_iscardTimeCountingDown = false;
			m_cardtime = 0;
			_eventDispatcher->dispatchCustomEvent("CardEnhanceSucceed");
		}
	}
}