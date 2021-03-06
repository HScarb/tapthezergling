// MainScene.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "CardControlLayer.h"
#include "NoTouchLayer.h"

class MainScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(MainScene);

private:
	void checkNewCard();						// 检测是否给一张新卡(每天只能给一张)

	virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event);
	virtual void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unused_event);

private:
	// UI触发事件
	void onSettingsBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);		// 设置按钮被点击
	void onCardBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);			// 卡片管理器按钮被点击
	void onAddJewelBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);		// 买宝石按钮被点击
private:
	// 狗
	cocos2d::Sprite * m_zergling;

	// 标签和按钮和进度条
	cocos2d::ui::Text * m_jewelText;
	cocos2d::ui::Text * m_energyText;
	cocos2d::ui::Text * m_scoreText;
	cocos2d::ui::Button * m_settingsBtn;
	cocos2d::ui::Button * m_cardBtn;
	cocos2d::ui::Button * m_addJewelBtn;
	cocos2d::ui::LoadingBar * m_energyBar;

	//层
	CardControlLayer * m_cardControlLayer;
	NoTouchLayer * m_noTouchLayer;

	//回复能量
	void resumeEnergy(float dt);
};