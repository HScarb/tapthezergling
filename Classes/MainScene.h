// MainScene.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"

class MainScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(MainScene);

private:
	// 标签和按钮和进度条
	cocos2d::ui::Text * m_jewelText;
	cocos2d::ui::Text * m_energyText;
	cocos2d::ui::Text * m_scoreText;
	cocos2d::ui::Button * m_settingsBtn;
	cocos2d::ui::Button * m_cardBtn;
	cocos2d::ui::Button * m_addJewelBtn;
	cocos2d::ui::LoadingBar * m_energyBar;
};