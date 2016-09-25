// SoundManager.cpp
#include "SoundManager.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace std;

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

void SoundManager::playMenuMusic()
{
	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() != true)
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/MainMenu.mp3");
	}
}

void SoundManager::forcePlayMenuMusic()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/MainMenu.mp3");
}

void SoundManager::playTollgateMusic()
{
	char * musicPath[2] =
	{
		"Sounds/Back2.mp3",
		"Sounds/Back3.mp3"
	};
	int i = random(0, 1);
	
	SimpleAudioEngine::getInstance()->playBackgroundMusic(musicPath[i]);
}

void SoundManager::stopMusic()
{
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void SoundManager::playEffect(string filePath)
{
	SimpleAudioEngine::getInstance()->playEffect(filePath.c_str());
}