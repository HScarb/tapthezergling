// GameManager.cpp
#include "GameManager.h"

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
	m_loop = 0;
	m_isGameOn = false;

	return true;
}