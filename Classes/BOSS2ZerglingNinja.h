// BOSS2ZerglingNinja
#pragma once
#include "cocos2d.h"
#include "TollgateControlLayer.h"
#include "ui\CocosGUI.h"

class BOSS2ZerglingNinja : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	CREATE_FUNC(BOSS2ZerglingNinja);
	virtual bool init() override;

	virtual bool onTouchBegan();

private:
	bool m_isRunning;
	TollgateControlLayer * m_controlLayer;
	std::vector<cocos2d::Vec2> m_posVector;
	cocos2d::Sprite * m_zerglingNinja;
};