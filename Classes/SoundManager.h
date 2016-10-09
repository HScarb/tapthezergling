#pragma once
#include "cocos2d.h"

class SoundManager : public cocos2d::Node
{
public:
	static SoundManager * getInstance();
	virtual bool init() override;

	// 播放菜单背景音乐
	void playMenuMusic();
	// 强制播放菜单背景音乐
	void forcePlayMenuMusic();
	// 播放关卡背景音乐
	void playTollgateMusic();
	// 停止背景音乐
	void stopMusic();

	// 播放音效
	void playEffect(std::string filePath);

	// 定义控制音乐开关的布尔变量
	CC_SYNTHESIZE(bool, m_musicOn, MusicOn);
	// 定义控制音效开关的布尔变量
	CC_SYNTHESIZE(bool, m_soundOn, SoundOn);

private:
	static SoundManager * m_soundManager;
};