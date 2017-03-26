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
	card->setCardLevel(level);//设置等级
	/*if (posY != 450)
	{
	card->setPosition(posX * 80, 0);//设定新增卡片的坐标
	InsertACard(card);
	}
	else
	{
	card->setPosition(450, 350);//设定合成后的卡片的坐标
	InsertCardAfterCollection(card);
	}*/
	if (posY == 0)
	{
		card->setPosition(0, 0);//设定新增卡片的坐标
		InsertACard(card);
	}
	else if (posY == 350)
	{
		card->setPosition(450, 350);//设定合成后的卡片的坐标
		setCardEnhanced(card);
	}
	/*if (posY == 300)
	{
	card->setPosition(450, 350);//设定合成后的卡片的坐标
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
	//得到最后一张卡片的位置
	for (auto card : m_cardVector)
	{
		i++;
	}
	card->setPosition((i++)*80, 0);//设定新增卡片的坐标
	InsertACard(card);
}

void CardManager::loadCardFromData()
{
	int enhanceCardType = -1;
	int enhanceCardLevel = -1;
	int enhanceCards = 0;
	if(DataManager::getInstance()->getEnhanceCardType() > 0)
	{
		enhanceCardType = DataManager::getInstance()->getEnhanceCardType();
		enhanceCardLevel = DataManager::getInstance()->getEnhanceCardLevel();
		enhanceCards = 2;
	}
	for (CardData* item : DataManager::getInstance()->getCardData())
	{
		// 每种卡片的数量
		// 是在Enhancer中的卡片
		if (item->info == enhanceCardType && item->level == enhanceCardLevel)
		{
			for (int i = 0; i < 2; i++)
			{
				Card* card = Card::createByLevelAndInfo(item->level, item->info);
				card->setPosition(300 + 300 * i, 300);
				InsertACardIntoEnhancer(card);
			}
			for (int i = 2; i < item->num; i++)
			{
				Card* card = Card::createByLevelAndInfo(item->level, item->info);
				InsertACard(card);
			}
		}
		else
		{
			for (int i = 0; i < item->num; i++)
			{
				Card* card = Card::createByLevelAndInfo(item->level, item->info);
				InsertACard(card);
			}
		}
	}
}

void CardManager::SortCardMsg(int diff)
{
	std::sort(m_cardVector.begin(), m_cardVector.end(), SortCardsOpreator);
	int i = 0;
	for (auto card : m_cardVector)
	{
		card->setPosition(i * 80 + diff, 0);
		i++;
	}
}

void CardManager::DeleteCardByObject(Card *card,float delta)
{
	m_cardVector.eraseObject(card);
	SortCardMsg(delta);
}

void CardManager::DeleteCardByObjectFromEnhancer(Card* card, float delta)
{
	m_cardInEnhancer.eraseObject(card);
	SortCardMsg(delta);
}

void CardManager::DeleteCardByObjectAfterCollection(Card* card,float delta)
{
//	free(m_cardEnhanced);
	m_cardEnhanced = nullptr;
	SortCardMsg(delta);
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

