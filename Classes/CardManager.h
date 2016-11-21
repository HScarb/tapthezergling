//cardManager.h
/*
	¿¨Æ¬¹ÜÀíÆ÷
	-¼ÇÂ¼¿¨Æ¬ÐÅÏ¢
	-ÔöÉ¾¿¨Æ¬²Ù×÷
	-¿¨Æ¬ÍÏ¶¯Ð§¹û
*/
#pragma once
#include "cocos2d.h"
#include "Card.h"

class CardManager : public cocos2d::Node
{
public:
	static CardManager * getInstance();
	virtual bool init();
	//·µ»Ø¿¨Æ¬´æ·ÅÈÝÆ÷
	cocos2d::Vector<Card*> getAllCards();
	cocos2d::Vector<Card*> getCardsFromEnhancer();
	cocos2d::Vector<Card*> getCardAfterCollection();

	void InsertACard(Card* card);
	void InsertACardIntoEnhancer(Card * card);
	void InsertCardAfterCollection(Card * card);
	void SortCardMsg();
	//É¾³ý¿¨Æ¬
	void DeleteCardByObject(Card * card);
	void DeleteCardByObjectFromEnhancer(Card * card);
	void DeleteCardByObjectAfterCollection(Card * card);

private:
	static CardManager * m_cardManager;
	cocos2d::Vector<Card*> m_cardVector;
	cocos2d::Vector<Card*> m_cardInEnhancer;
	cocos2d::Vector<Card*> m_cardAfterCollection;
};

inline bool SortCardsOpreator(const Card* card1, const Card* card2);
