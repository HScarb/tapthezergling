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

	m_isCountingDown = false;		// 设置正在倒数为false
	this->scheduleUpdate();			// 开始调用update函数

	return true;
}

void TimeManager::addTime(float t)
{
	m_time += t;
}

void TimeManager::reduceTime(float t)
{
	m_time -= t;
}

void TimeManager::startCountDown()
{
	m_isCountingDown = true;
}

void TimeManager::pauseCountDown()
{
	m_isCountingDown = false;
}

void TimeManager::update(float dt)
{
	if (m_isCountingDown)		// 如果正在倒数，那么减少总时间
		m_time -= dt;
}