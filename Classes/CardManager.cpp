//CardManager.cpp
#include "CardManager.h"
#include "Card.h"
#include "GameManager.h"
#include "DataManager.h"
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

	m_cardEnhanced = nullptr;

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

Card* CardManager::CreateACardByTypeAndLevel(int info, int level, float posY)
{
	Card * card = nullptr;
	if (info == 0)
		return nullptr;
	card = Card::createByLevelAndInfo(level, info);
	card->setCardLevel(level);//���õȼ�
	/*if (posY != 450)
	{
	card->setPosition(posX * 80, 0);//�趨������Ƭ������
	InsertACard(card);
	}
	else
	{
	card->setPosition(450, 350);//�趨�ϳɺ�Ŀ�Ƭ������
	InsertCardAfterCollection(card);
	}*/
	if (posY == 0)
	{
		card->setPosition(0, 0);//�趨������Ƭ������
		InsertACard(card);
	}
	else if (posY == 350)
	{
		card->setPosition(450, 350);//�趨�ϳɺ�Ŀ�Ƭ������
		setCardEnhanced(card);
	}
	/*if (posY == 300)
	{
	card->setPosition(450, 350);//�趨�ϳɺ�Ŀ�Ƭ������
	InsertCardAfterCollection(card);
	}*/
	else if (posY == -1)
	{
		InsertChestCard();
	}
	return card;
}

void CardManager::InsertACard(Card * card)
{
	m_cardVector.pushBack(card);
}

void CardManager::InsertACardIntoEnhancer(Card* card)
{
	m_cardInEnhancer.pushBack(card);
}

void CardManager::InsertChestCard()
{
	Card * card;
	int type = /*GameManager::getInstance()->getcardType();*/0;
	card = Card::createByLevelAndInfo(1, type);
	int i = 0;
	//�õ����һ�ſ�Ƭ��λ��
	for (auto card : m_cardVector)
	{
		i++;
	}
	card->setPosition((i++)*80, 0);//�趨������Ƭ������
	InsertACard(card);
}

void CardManager::loadCardFromData()
{
	for (CardData* item : DataManager::getInstance()->getCardData())
	{
		// ÿ�ֿ�Ƭ������
		for (int i = 0; i < item->num; i++)
		{
			Card* card = Card::createByLevelAndInfo(item->level, item->info);
			InsertACard(card);
		}
	}
}

void CardManager::SortCardMsg()
{
	std::sort(m_cardVector.begin(), m_cardVector.end(), SortCardsOpreator);
	int i = 0;
	for (auto card : m_cardVector)
	{
		card->setPosition(i * 80, 0);
		i++;
	}
}

void CardManager::DeleteCardByObject(Card *card)
{
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
//	free(m_cardEnhanced);
	m_cardEnhanced = nullptr;
	SortCardMsg();
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

