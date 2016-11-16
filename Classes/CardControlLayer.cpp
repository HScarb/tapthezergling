//CardControlLayer.cpp
#include"CardControlLayer.h"
#include "cocostudio/CocoStudio.h"
#include "CardManager.h"
const int CARD_SLOT_Y = 300;
const int CARD_SLOT_X1 = 300;
const int CARD_SLOT_X2 = 600;

USING_NS_CC;
using namespace cocos2d::ui;

Scene* CardControlLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = CardControlLayer::create();
	scene->addChild(scene);
	return scene;
}

bool CardControlLayer::init()
{
	if (!Layer::init())
		return false;

	m_collectBtn = nullptr;
	m_closeBtn = nullptr;
	m_operatingCard = nullptr;
	m_sameCardsInVector = 0;
	m_isEnhancerContaninsACard = false;
	m_isSingleCard = false;
	auto ui = CSLoader::createNode("CardEnhancer.csb");
	this->addChild(ui);
	// 创建一个无触摸层，在卡片控制层的下面
	/*m_noTouchLayer = NoTouchLayer::create();
	this->addChild(m_noTouchLayer, 0);*/
	//从ui中加载按钮
	m_closeBtn = (Button *)ui->getChildByName("Button_x");
	m_collectBtn = (Button *)ui->getChildByName("Button_collect");
/*	//从ui中加载卡片滑动视图
	m_cardView = (ScrollView *)ui->getChildByName("cardView");*/
	//加载manager里的卡片容器
	m_CardMsg = CardManager::getInstance()->getAllCards();
	m_CardBeforeEnhancer = CardManager::getInstance()->getCardsFromEnhancer();
	m_CardAfterEnhancer = CardManager::getInstance()->getCardAfterEnhancer();
	if (m_CardMsg.size() == 0)
	{
		//创建卡片
		for (int i = 17; i >= 1; i--)
		{
			if (i > 10)
			{
				CreateACard(i - 10, 1, i - 1);
			}
			else
				CreateACard(i, 1, i - 1);
		}
	}
	else
		showCards();

	//CardManager::getInstance()->DeleteCardByObject(5, 1);
	CardManager::getInstance()->SortCardMsg();;

	//获取屏幕分辨率
	auto glView = Director::getInstance()->getOpenGLView();
	m_frameSize = glView->getFrameSize();
	log("size=%f", m_frameSize.width);

	//触控监听
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CardControlLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(CardControlLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(CardControlLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	listener->setSwallowTouches(true);
	m_closeBtn->addTouchEventListener(this, toucheventselector(CardControlLayer::onCloseBtnClick));
	m_collectBtn->addTouchEventListener(this, toucheventselector(CardControlLayer::onCollectBtnClick));
	return true;

}

void CardControlLayer::CreateACard(int info,int level,int posX)
{
	CardManager::getInstance()->InsertACard(CreateACardByTypeAndLevel(
		(Card::CardInfo)info, level, posX));
}

void CardControlLayer::DeleteACard(Card* card)
{
	CardManager::getInstance()->DeleteCardByObject(card);
	card->removeFromParent();
}

void CardControlLayer::MoveCardIntoEnhancer(Card* card)
{
	if (card->getPosition().x >= (CARD_SLOT_X1 - 50) && card->getPosition().x <= (CARD_SLOT_X1 + 50))
		card->setPosition(CARD_SLOT_X1, CARD_SLOT_Y);
	else if (card->getPosition().x >= (CARD_SLOT_X2 - 50) && card->getPosition().x <= (CARD_SLOT_X2 + 50))
		card->setPosition(CARD_SLOT_X2, CARD_SLOT_Y);
	else
		return;
	CardManager::getInstance()->InsertACardIntoEnhancer(card);
	CardManager::getInstance()->DeleteCardByObject(card);
}

void CardControlLayer::onCloseBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		this->removeFromParent();
	}
}
void CardControlLayer::onCollectBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	
}

Card* CardControlLayer::CreateACardByTypeAndLevel(Card::CardInfo info, int level,int posX)
{
	Card * card = nullptr;
	if (info == 0)
		return nullptr;
	card = Card::createByInfo(info);
	card->setCardLevel(level);//设置等级
	card->setPosition(posX * 80, 0);
	this->addChild(card);
	return card;
}

void CardControlLayer::showCards()
{
	for (auto card : CardManager::getInstance()->getAllCards())
	{
		this->addChild(card);
	}
	for (auto card : CardManager::getInstance()->getCardsFromEnhancer())
	{
		this->addChild(card);
	}
}

void CardControlLayer::CardAfterEnhancer(Card* card)
{

}

void CardControlLayer::ClickCardBackToBottom(Card* card)
{
	CardManager::getInstance()->InsertACard(card);
	CardManager::getInstance()->DeleteCardByObjectFromEnhancer(card);
	//reShowCards();
}

bool CardControlLayer::IsTheSameCardInEnhancer(Card* card)
{
	for (auto card1 : CardManager::getInstance()->getCardsFromEnhancer())
	{
		if (card->getCardinfo() == card1->getCardinfo() && card->getCardLevel() == card1->getCardLevel())
			return true;
		else
			return false;
	}
}

bool CardControlLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	
	m_beginPos = touch->getLocation();
	log("x=%f",m_beginPos.x);
	for (auto card : CardManager::getInstance()->getCardsFromEnhancer())
	{
		if (card->getBoundingBox().containsPoint(m_beginPos))
		{
			log("11111");
			if (CardManager::getInstance()->getCardsFromEnhancer().size()>0)
				ClickCardBackToBottom(card);
		}
	}
	return true;
}

void CardControlLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	Rect rect;
	m_delta = touch->getDelta();
	m_movedPos = touch->getLocation();
	// 卡片滑动
	// 当滑动x轴距离大于10时才开始滑动，当点击开始点和目前点y轴大于80时不能滑动
	if (m_operatingCard == nullptr && abs(m_beginPos.x - m_movedPos.x) >= 10 && m_movedPos.y <= 80 && m_beginPos.y <= 80)
	{
		//auto cards = CardManager::getInstance()->getAllCards();
		if (CardManager::getInstance()->getAllCards().size() >= m_frameSize.width / 80)
		{
			for (auto card : CardManager::getInstance()->getAllCards())
			{
				auto pos = card->getPosition();
				card->setPosition(pos.x + m_delta.x, 0);
			}
		}
	}
	// 把卡片移动到卡片管理器

	if (abs(m_movedPos.y - m_beginPos.y) >= 40)
	{
		for (auto card : CardManager::getInstance()->getAllCards())
		{
			if (card->getBoundingBox().containsPoint(m_beginPos))
			{
				m_operatingCard = card;
				m_operatingCard->setPosition(m_movedPos.x - 40, m_movedPos.y - 40);
			}
		}
	}
	if (m_operatingCard != nullptr)
	{
		/*if (m_isSingleCard == false)
		{
			//判断电机的卡片在卡片容器和合成器中数目之和是否超过1
			for (auto card : CardManager::getInstance()->getAllCards())
			{
				if (card->getCardLevel() == m_operatingCard->getCardLevel() && card->getCardinfo() == m_operatingCard->getCardinfo())
					m_sameCardsInVector++;
				log("card %d amount %d", m_operatingCard->getCardinfo(), m_sameCardsInVector);
			}
			if (m_sameCardsInVector == 1)
			{
				if (CardManager::getInstance()->getCardsFromEnhancer().size() > 0)
				{
					for (auto card : CardManager::getInstance()->getCardsFromEnhancer())
					{
						if (card->getCardLevel() == m_operatingCard->getCardLevel() && card->getCardinfo() == m_operatingCard->getCardinfo())
							m_sameCardsInVector++;
						log("card %d amount %d", m_operatingCard->getCardinfo(), m_sameCardsInVector);
					}
					log("card %d amount %d", m_operatingCard->getCardinfo(), m_sameCardsInVector);
				}
				else
				{
					m_operatingCard = nullptr;
					m_isSingleCard = true;
					CardManager::getInstance()->SortCardMsg();
					m_sameCardsInVector = 0;
				}
			}
		}
		if (m_isSingleCard == false)*/
			m_operatingCard->setPosition(m_movedPos.x - 40, m_movedPos.y - 40);
	}	
}

void CardControlLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	m_endPos = touch->getLocation();

	// 如果只是滑动，没有操作卡片，判断是否是点击卡片显示卡片信息
	if (m_operatingCard == nullptr)
	{
		if (m_endPos.y <= 80)
		{
			if (abs(m_beginPos.x - m_endPos.x) < 10)
			{
				for (auto card : CardManager::getInstance()->getAllCards())
				{
					if (card->getBoundingBox().containsPoint(m_endPos) && m_beginPos.y <= 80)
					{
						log("info=%d local x=%f,y=%f", card->getCardinfo(), card->getPosition().x, card->getPosition().y);
						//DeleteACard(card);
						m_cardInfoLayer = CardInfoLayer::create(card->getCardinfo(), card->getCardLevel());
						this->addChild(m_cardInfoLayer);
						break;
					}
				}
			}
		}
		return;
	}

	// 如果卡片移动的终点在卡片合成器卡槽附近的范围，那就把卡片直接移动进卡槽
	// 如果卡片移动终点坐标y轴范围在[300,400],x轴坐标在[300,400]或者[600,700]时
	if (m_operatingCard->getPosition().y >= (CARD_SLOT_Y - 50)
		&& m_operatingCard->getPosition().y <= (CARD_SLOT_Y + 50)
		&&
			(m_operatingCard->getPosition().x >= (CARD_SLOT_X1 - 50)
			&& m_operatingCard->getPosition().x <= (CARD_SLOT_X1 + 50)
			|| m_operatingCard->getPosition().x >= (CARD_SLOT_X2 - 50)
			&& m_operatingCard->getPosition().x <= (CARD_SLOT_X2 + 50)))
	{
		/*if (m_isEnhancerContaninsACard)
		{
			if (IsTheSameCardInEnhancer(m_operatingCard))
			{
				for (auto card : CardManager::getInstance()->getCardsFromEnhancer())
				{
					if (CardManager::getInstance()->getCardsFromEnhancer().size() > 0)
					{
						if (m_operatingCard->getPosition().x >= (card->getPosition().x - 50)
							&& m_operatingCard->getPosition().x <= (card->getPosition().x + 50))
						{
							m_operatingCard = nullptr;
							break;
						}
					}
				}
				MoveCardIntoEnhancer(m_operatingCard);
				m_operatingCard = nullptr;
			}
			else
			{
				m_operatingCard = nullptr;
				CardManager::getInstance()->SortCardMsg();
			}
		}
		else
		{
			MoveCardIntoEnhancer(m_operatingCard);
			m_operatingCard = nullptr;
		}*/
		MoveCardIntoEnhancer(m_operatingCard);
		m_operatingCard = nullptr;
	}
	else
	{
		m_operatingCard = nullptr;
		CardManager::getInstance()->SortCardMsg();
	}
	//m_isSingleCard = false;

	
	
}