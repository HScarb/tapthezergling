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
	m_iscardTimeCountingDown = false;	//设置卡片倒数为false
	m_isCountingDown = false;		// 设置正在倒数为false
	m_isTollgateBegin = false;
	this->scheduleUpdate();			// 开始调用update函数
	

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
	m_isTollgateBegin = true;		// 关卡开始倒计时
	m_preTime = m_time;
}

void TimeManager::pauseCountDown()
{
	m_isCountingDown = false;
}

void TimeManager::resumeCountDown()
{
	// 如果关卡已经开始，恢复时开启倒计时。如果关卡没有开始，无动作
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
	if (m_isCountingDown)		// 如果正在倒数，那么减少总时间
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