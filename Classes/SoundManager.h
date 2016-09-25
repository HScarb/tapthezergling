#pragma once
#include "cocos2d.h"

class SoundManager : public cocos2d::Node
{
public:
	static SoundManager * getInstance();
	virtual bool init() override;

	// ���Ų˵���������
	void playMenuMusic();
	// ǿ�Ʋ��Ų˵���������
	void forcePlayMenuMusic();
	// ���Źؿ���������
	void playTollgateMusic();
	// ֹͣ��������
	void stopMusic();

	// ������Ч
	void playEffect(std::string filePath);

private:
	static SoundManager * m_soundManager;
};