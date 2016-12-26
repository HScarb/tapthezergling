//cardManager.h
/*
	卡片管理器
	-记录卡片信息
	-增删卡片操作
	-卡片拖动效果
*/
#pragma once
#include "cocos2d.h"
#include "Card.h"

class CardManager : public cocos2d::Node
{
public:
	static CardManager * getInstance();
	virtual bool init();
	//返回卡片存放容器
	cocos2d::Vector<Card*> getAllCards();
	cocos2d::Vector<Card*> getCardsFromEnhancer();
	cocos2d::Vector<Card*> getCardAfterCollection();

	//通过卡片信息，等级往容器中增加卡片
	Card * CreateACardByTypeAndLevel(Card::CardInfo info, int level, int posX);
	//Card * CreateACardByTypeAndLevel(Card * card);
	void InsertACard(Card* card);
	void InsertACardIntoEnhancer(Card * card);
	void InsertCardAfterCollection(Card * card);
	void SortCardMsg();
	//删除卡片
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
