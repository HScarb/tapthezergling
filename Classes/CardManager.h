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

	//ͨ����Ƭ��Ϣ���ȼ������������ӿ�Ƭ
	Card * CreateACardByTypeAndLevel(int info, int level, float posY);
	//Card * CreateACardByTypeAndLevel(Card * card);
	void InsertACard(Card* card);
	void InsertACardIntoEnhancer(Card * card);
	void SortCardMsg();
	void InsertChestCard();
	// ��DataManager���������뿨Ƭ
	void loadCardFromData();
	//ɾ����Ƭ
	void DeleteCardByObject(Card * card);
	void DeleteCardByObjectFromEnhancer(Card * card);
	void DeleteCardByObjectAfterCollection(Card * card);

private:
	static CardManager * m_cardManager;

	cocos2d::Vector<Card*> m_cardVector;
	cocos2d::Vector<Card*> m_cardInEnhancer;

	CC_SYNTHESIZE(Card*, m_cardEnhanced, CardEnhanced);
};

inline bool SortCardsOpreator(const Card* card1, const Card* card2);
