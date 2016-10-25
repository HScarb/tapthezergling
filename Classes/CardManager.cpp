//CardManager.cpp

#include "CardManager.h"
USING_NS_CC;

CardManager * CardManager::m_cardManager = nullptr;

CardManager* CardManager::getInstance()
{
	if (m_cardManager == nullptr)
	{
		m_cardManager->autorelease();
		m_cardManager->retain();
	}
	else
	{
		CC_SAFE_DELETE(m_cardManager);
		m_cardManager = nullptr;
	}
	return m_cardManager;
}

bool CardManager::init()
{
	if (!Node::init())
		return false;
	/*m_CardView->m_cardView;
	m_CardContainer->m_cardContainer;
	m_cardMsg.pushBack(CreateACard());*/
	return true;
}

/*Sprite* CardManager::CreateACard()
{
	Sprite *card = Sprite::create("Res/Cards/Card_1.png");
	card->setPosition(50, 250);
	m_CardContainer->addChild(card);
	return card;
}*/

/*Card* CardManager::CreateACard(Card::CardInfo info)
{
	Card * card = nullptr;
	if (info == 0)
		return nullptr;
	card = Card::createByInfo(info);
	card->setPosition(50, 250);
	m_CardContainer->addChild(card);
	return card;
}*/



bool CardManager::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	return true;
}

void CardManager::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
}

void CardManager::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
}