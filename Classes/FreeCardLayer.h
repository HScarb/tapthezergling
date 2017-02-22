#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "Card.h"

class Card;

class FreeCardLayer :public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int info);
	virtual bool init(int info);
	static FreeCardLayer * create(int info);

private:
	void onClaimBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
	//按钮
	cocos2d::ui::Button * m_claimBtn;				// 认领按钮

	//信息
	cocos2d::ui::Text * m_cardName;					// 卡片名字

	// 卡片
	Card* m_card;
};