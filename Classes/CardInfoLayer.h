//CardInfoLayer.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "Card.h"

class Card;

class CardInfoLayer :public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int info ,int level);
	virtual bool init(int info ,int level) ;
	static CardInfoLayer * create(int info, int level);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	void onCloseBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
	//∞¥≈•
	cocos2d::ui::Button * m_closeBtn;

	//–≈œ¢
	cocos2d::ui::Text * m_cardName;
	cocos2d::ui::Text * m_cardInfo;
	cocos2d::ui::Text * m_cardLevel;
	int m_info;
	int m_level;
};