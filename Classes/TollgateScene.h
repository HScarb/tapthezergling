// TollgateScene.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"

class TollgateScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(TollgateScene);

private:
	void onHomeBtnClicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onCardBtnClicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	
	void onItem1Clicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onItem2Clicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onItem3Clicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onItem4Clicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onItem5Clicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onItem6Clicked(Ref * pSender, cocos2d::ui::TouchEventType type);

private:
	// 标签和按钮和进度条
	cocos2d::ui::Text * m_jewelText;
	cocos2d::ui::Text * m_energyText;
	cocos2d::ui::Button * m_homeBtn;
	cocos2d::ui::Button * m_cardBtn;
	cocos2d::ui::Button * m_addJewelBtn;
	cocos2d::ui::LoadingBar * m_energyBar;
	cocos2d::ui::LoadingBar * m_timeBar;
	cocos2d::ui::Text * m_timeText;

	cocos2d::ui::ScrollView * m_scrollView;

	// 每个关卡的按钮
	cocos2d::ui::Text * m_t1;
	cocos2d::ui::Text * m_t2;
	cocos2d::ui::Text * m_t3;
	cocos2d::ui::Text * m_t4;
	cocos2d::ui::Text * m_t5;
	cocos2d::ui::Text * m_t6;
};