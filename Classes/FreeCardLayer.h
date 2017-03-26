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
	//��ť
	cocos2d::ui::Button * m_claimBtn;				// ���찴ť

	//��Ϣ
	cocos2d::ui::Text * m_cardName;					// ��Ƭ����

	// ��Ƭ
	Card* m_card;
};