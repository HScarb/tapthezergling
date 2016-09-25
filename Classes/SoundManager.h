#pragma once
#include "cocos2d.h"

class SoundManager : public cocos2d::Node
{
public:
	static SoundManager * getInstance();
	virtual bool init() override;

	

private:
	static SoundManager * m_soundManager;
};