// SettingsScene.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"

class SettingsScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	CREATE_FUNC(SettingsScene);
	virtual bool init() override;

private:
	void onHomeBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);

private:
	// °´Å¥
	cocos2d::ui::Button * m_homeBtn;
	cocos2d::ui::Button * m_soundBtn;
	cocos2d::ui::Button * m_musicBtn;
	cocos2d::ui::Button * m_restoreBtn;
	cocos2d::ui::Button * m_aboutBtn;
};
