//cardManager.h
/*
	��Ƭ������
	-��¼��Ƭ��Ϣ
	-��ɾ��Ƭ����
	-��Ƭ�϶�Ч��
*/
#pragma once
#include "Card.h"
#include "cocos2d.h"
#include "CardControlLayer.h"

class CardManager : public cocos2d::Node
{
public:
	static CardManager * getInstance();
	virtual bool init();


	/*Card *CreateACard(Card::CardInfo info);
	Sprite * CreateACard();*/

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	static CardManager * m_cardManager;
	/*CardControlLayer * m_CardView;
	CardControlLayer * m_CardContainer;
	Vector<Card*> m_cardMsg;
	Vector<Sprite*>m_cardMsg;*/
};