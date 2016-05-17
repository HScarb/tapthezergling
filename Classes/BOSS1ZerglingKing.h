// BOSS1ZerglingKing.h
#pragma once
#include "cocos2d.h"
#include "TollgateControlLayer.h"
#include "ui\CocosGUI.h"
const int TOUCH_SUM = 15;

class BOSS1ZerglingKing : cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	CREATE_FUNC(BOSS1ZerglingKing);
	virtual bool init();

	virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);

private:
	bool m_isRunning;
	int m_hitPoint;
	TollgateControlLayer * m_controlLayer;
	cocos2d::Sprite * m_zerglingKing;
};
