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
	return m_cardVector;
}

cocos2d::Vector<Card*> CardManager::getCardsFromEnhancer()
{
	return m_cardInEnhancer;
}

cocos2d::Vector<Card*> CardManager::getCardAfterCollection()
{
	return m_cardAfterCollection;
}

void CardManager::InsertACard(Card * card)
{
	m_cardVector.pushBack(card);
}

void CardManager::InsertACardIntoEnhancer(Card* card)
{
	m_cardInEnhancer.pushBack(card);
}

void CardManager::InsertCardAfterCollection(Card* card)
{
	m_cardAfterCollection.pushBack(card);
}

void CardManager::SortCardMsg()
{
	std::sort(m_cardVector.begin(), m_cardVector.end(),SortCardsOpreator);
	int i = 0;
	for (auto card : m_cardVector)
	{
		card->setPosition(i * 80, 0);
		i++;
	}
}

void CardManager::DeleteCardByObject(Card *card)
{ 
	/*int pos = 0;
	for (auto card : m_cardVector)
	{
		if (card->getCardinfo() == type && card->getCardLevel() == level)
		{
			break;
		}
		pos++;
	}*/
	m_cardVector.eraseObject(card);
	SortCardMsg();
}

void CardManager::DeleteCardByObjectFromEnhancer(Card* card)
{
	m_cardInEnhancer.eraseObject(card);
	SortCardMsg();
}

void CardManager::DeleteCardByObjectAfterCollection(Card* card)
{
	m_cardAfterCollection.eraseObject(card);
	SortCardMsg();
}

bool SortCardsOpreator(const Card* card1, const Card* card2)
{
	if (card1->getCardinfo() == card2->getCardinfo())
	{
		return (card1->getCardLevel()) < (card2->getCardLevel());
	}
	else
	{
		return card1->getCardinfo() < card2->getCardinfo();
	}

}
