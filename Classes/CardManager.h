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
#include "ui\CocosGUI.h"

class CardManager : public cocos2d::Node
{
public:
	static CardManager * getInstance();
	virtual bool init();
	//���ؿ�Ƭ�������
	cocos2d::Vector<Card*> getAllCards();
	void InsertACard(Card* card);
	void SortCardMsg();
	//ɾ����Ƭ
	void DeleteCardByTypeAndLevel(int type,int level);
	
private:
	static CardManager * m_cardManager;
	cocos2d::Vector<Card*> m_cardMsg;
};

inline bool SortCardsOpreator(const Card* card1, const Card* card2);
