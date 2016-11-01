//CardManager.cpp
#include "CardManager.h"
#include "Card.h"
USING_NS_CC;

CardManager * CardManager::m_cardManager = nullptr;

CardManager* CardManager::getInstance()
{
	
	if (m_cardManager == nullptr)
	{
		m_cardManager = new CardManager();
		if (m_cardManager&&m_cardManager->init())
		{
			m_cardManager->autorelease();
			m_cardManager->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_cardManager);
			m_cardManager = nullptr;
		}
	}
	return m_cardManager;
}

bool CardManager::init()
{
	if (!Node::init())
		return false;
	return true;
}

cocos2d::Vector<Card*> CardManager::getAllCards()
{
	return m_cardMsg;
}

void CardManager::InsertACard(Card * card)
{
	m_cardMsg.pushBack(card);
}

void CardManager::SortCardMsg()
{
	std::sort(m_cardMsg.begin(), m_cardMsg.end(),SortCardsOpreator);
}

void CardManager::DeleteCardByTypeAndLevel(int type,int level)
{ 
	int pos = 0;
	for (auto card : m_cardMsg)
	{
		log("info %d,level %d", card->getCardinfo(), card->getCardLevel());
		if ((card->getCardinfo()) == type && (card->getCardLevel()) == level)
		{
			break;
		}
		pos++;
	}
	m_cardMsg.erase(pos);
}

bool SortCardsOpreator(const Card* card1, const Card* card2)
{
	if (card1->getCardinfo() == card2->getCardinfo())
	{
		return (card2->getCardLevel()) < (card1->getCardLevel());
	}
	else
	{
		return card1->getCardinfo() < card2->getCardinfo();
	}

}
