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

	m_isCountingDown = false;		// �������ڵ���Ϊfalse
	this->scheduleUpdate();			// ��ʼ����update����

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
	if (m_isCountingDown)		// ������ڵ�������ô������ʱ��
		m_time -= dt;
}