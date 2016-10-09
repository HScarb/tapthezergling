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

	m_musicOn = true;
	m_soundOn = true;

	return true;
}

// 如果音乐控制开关为真，同时没有其他背景音乐在播放，播放菜单背景音乐
void SoundManager::playMenuMusic()
{
	if(m_musicOn)		
	{
		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() != true)
		{
			SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/MainMenu.mp3");
		}
	}
}

// 如果音乐控制开关为真，不管有没有其他背景音乐播放，强制替换播放菜单背景音乐
void SoundManager::forcePlayMenuMusic()
{
	if(m_musicOn)
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/MainMenu.mp3");
	}
}

// 随机播放关卡背景音乐
void SoundManager::playTollgateMusic()
{
	if(m_musicOn)
	{
		char * musicPath[2] =
			{
				"Sounds/Back2.mp3",
				"Sounds/Back3.mp3"
			};
		int i = random(0, 1);
	
		SimpleAudioEngine::getInstance()->playBackgroundMusic(musicPath[i]);
	}
}

void SoundManager::stopMusic()
{
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// 如果音效开关为真，播放音效
void SoundManager::playEffect(string filePath)
{
	if(m_soundOn)
	{
		SimpleAudioEngine::getInstance()->playEffect(filePath.c_str());
	}
}