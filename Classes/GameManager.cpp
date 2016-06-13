// GameManager.cpp
#include "GameManager.h"
#include "TimeManager.h"
USING_NS_CC;

GameManager * GameManager::m_gameManager = nullptr;

GameManager* GameManager::getInstance()
{
	if(m_gameManager == nullptr)
	{
		m_gameManager = new GameManager();
		if(m_gameManager && m_gameManager->init())
		{
			m_gameManager->autorelease();
			m_gameManager->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_gameManager);
			m_gameManager = nullptr;
		}
	}
	return m_gameManager;
}

bool GameManager::init()
{
	if (!Node::init())
		return false;

	m_tollgate = 0;
	m_nextTollgate = 0;
	m_score = 0;
	m_tollgateNum = 0;
	m_jewel = 0;
	m_energy = 0;
	m_diff = 0;
	m_loop = 1;
	m_isGameOn = false;

	return true;
}

void GameManager::setNextTollgate(int i)
{
	// ÉèÖÃ·ÖÊý
	m_score = m_score + (int)TimeManager::getInstance()->getTime() + m_loop * 5 + m_tollgateNum * 2;
	
	m_nextTollgate = i;
	m_tollgateNum++;
	if (m_tollgateNum < 10)
	{
		m_diff = 0;
		m_loop = 1;
	}
	else if (m_tollgateNum <= 15)
	{
		m_diff = 1;
		m_loop = 2;
	}
	else if (m_tollgateNum < 20)
	{
		m_diff = 1;
		m_loop = random(1, 3);
	}
	else if (m_tollgateNum < 25)
	{
		m_diff = random(1, 2);
		m_loop = random(1, 3);
	}
	else if (m_tollgateNum < 30)
	{
		m_diff = 2;
		m_loop = random(2, 3);
	}
	else if (m_tollgateNum < 40)
	{
		m_diff = 2;
		m_loop = 3;
	}

}

int GameManager::getNextTollgate()
{
	return m_nextTollgate;
}

void GameManager::resetTollgateData()
{
	m_tollgate = 0;
	m_nextTollgate = 0;
	m_score = 0;
	m_tollgateNum = 0;
	m_diff = 0;
	m_loop = 0;
	m_isGameOn = false;
}
