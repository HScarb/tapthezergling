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
#include "ui\CocosGUI.h"

class CardManager : public cocos2d::Node
{
public:
	static CardManager * getInstance();
	virtual bool init();
	//返回卡片存放容器
	cocos2d::Vector<Card*> getAllCards();
	void InsertACard(Card* card);
	void SortCardMsg();
	//删除卡片
	void DeleteCardByTypeAndLevel(int type,int level);
	
private:
	static CardManager * m_cardManager;
	cocos2d::Vector<Card*> m_cardMsg;
};

inline bool SortCardsOpreator(const Card* card1, const Card* card2);
