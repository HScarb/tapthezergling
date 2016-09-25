#pragma once
#include "cocos2d.h"

class SoundManager : public cocos2d::Node
{
public:
	static SoundManager * getInstance();
	virtual bool init() override;

	// ≤•∑≈≤Àµ•±≥æ∞“Ù¿÷
	void playMenuMusic();
	// «ø÷∆≤•∑≈≤Àµ•±≥æ∞“Ù¿÷
	void forcePlayMenuMusic();
	// ≤•∑≈πÿø®±≥æ∞“Ù¿÷
	void playTollgateMusic();
	// Õ£÷π±≥æ∞“Ù¿÷
	void stopMusic();

	// ≤•∑≈“Ù–ß
	void playEffect(std::string filePath);

private:
	static SoundManager * m_soundManager;
};