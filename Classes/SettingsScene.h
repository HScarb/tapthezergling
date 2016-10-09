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
	//cocos2d::FontShadow _shadow;

private:
	void onHomeBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onSoundBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onMusciBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onRestoreBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onAboutBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);

private:
	// °´Å¥
	cocos2d::ui::Button * m_homeBtn;
	cocos2d::ui::Button * m_soundBtn;
	cocos2d::ui::Button * m_musicBtn;
	cocos2d::ui::Button * m_restoreBtn;
	cocos2d::ui::Button * m_aboutBtn;
	// ÎÄ±¾
	cocos2d::ui::Text * m_soundText;
	cocos2d::ui::Text * m_musicText;
};
