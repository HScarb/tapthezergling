//cardManager.h
/*
	��Ƭ������
	-��¼��Ƭ��Ϣ
	-��ɾ��Ƭ����
	-��Ƭ�϶�Ч��
*/
#pragma once
#include "cocos2d.h"
#include "Card.h"

class CardManager : public cocos2d::Node
{
public:
	static CardManager * getInstance();
	virtual bool init();
	//���ؿ�Ƭ�������
	cocos2d::Vector<Card*> getAllCards();
	cocos2d::Vector<Card*> getCardsFromEnhancer();
	cocos2d::Vector<Card*> getCardAfterEnhancer();

	void InsertACard(Card* card);
	void InsertACardIntoEnhancer(Card * card);
	void InsertACardToAEnhancer(Card * card);
	void SortCardMsg();
	//ɾ����Ƭ
	void DeleteCardByObject(Card * card);
	void DeleteCardByObjectFromEnhancer(Card * card);

private:
	static CardManager * m_cardManager;
	cocos2d::Vector<Card*> m_cardVector;
	cocos2d::Vector<Card*> m_cardInEnhancer;
	cocos2d::Vector<Card*> m_cardAfterEnhancer;
};

inline bool SortCardsOpreator(const Card* card1, const Card* card2);
