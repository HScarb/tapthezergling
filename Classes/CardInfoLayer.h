//CardInfoLayer.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "Card.h"

class Card;

class CardInfoLayer :public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init() override;
	CREATE_FUNC(CardInfoLayer);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	void onCloseBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
	//��ť
	cocos2d::ui::Button * m_closeBtn;

	//��Ϣ
	cocos2d::ui::Text * m_cardName;
	cocos2d::ui::Text * m_cardInfo;
};