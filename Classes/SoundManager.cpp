// SoundManager.cpp
#include "SoundManager.h"
USING_NS_CC;

SoundManager * SoundManager::m_soundManager = nullptr;

SoundManager* SoundManager::getInstance()
{
	if(m_soundManager == nullptr)
	{
		m_soundManager = new SoundManager();
		if(m_soundManager && m_soundManager->init())
		{
			m_soundManager->autorelease();
			m_soundManager->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_soundManager);
			m_soundManager = nullptr;
		}
	}
	return m_soundManager;
}

bool SoundManager::init()
{
	if (!Node::init())
		return false;



	return true;
}