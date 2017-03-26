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

	//通过卡片信息，等级往容器中增加卡片
	Card * CreateACardByTypeAndLevel(int info, int level, float posY);
	//Card * CreateACardByTypeAndLevel(Card * card);
	void InsertACard(Card* card);
	void InsertACardIntoEnhancer(Card * card);
	void SortCardMsg(int diff = 0);
	void InsertChestCard();
	// 从DataManager数据中载入卡片
	void loadCardFromData();
	//删除卡片
	void DeleteCardByObject(Card * card,float delta = 0);
	void DeleteCardByObjectFromEnhancer(Card * card, float delta = 0);
	void DeleteCardByObjectAfterCollection(Card * card, float delta = 0);
private:
	static CardManager * m_cardManager;

	cocos2d::Vector<Card*> m_cardVector;
	cocos2d::Vector<Card*> m_cardInEnhancer;

	CC_SYNTHESIZE(Card*, m_cardEnhanced, CardEnhanced);
};

inline bool SortCardsOpreator(const Card* card1, const Card* card2);
