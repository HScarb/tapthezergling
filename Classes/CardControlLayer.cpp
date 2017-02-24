//CardControlLayer.cpp
#include"CardControlLayer.h"
#include "cocostudio/CocoStudio.h"
#include "CardManager.h"
#include "TimeManager.h"
#include "DataManager.h"
#include "GameManager.h"
const int CARD_SLOT_Y = 300;
const int CARD_SLOT_X1 = 300;
const int CARD_SLOT_X2 = 600;

USING_NS_CC;
using namespace ui;
using namespace std;

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
	m_currentTime = getCurrentTime();
	//m_timeStamp = getTimeStamp();
	//log("cardtime %d,et %d", DataManager::getInstance()->getStartTimeStamp(), DataManager::getInstance()->getEndingTimeStamp());
	m_collectBtn = nullptr;
	m_closeBtn = nullptr;
	m_operatingCard = nullptr;
	m_isCardsStartEnhance = false;
	m_isSingleCard = true;
	m_cardEnhanceTime = nullptr;
	m_deltaX = 0;
	auto ui = CSLoader::createNode("CardEnhancer.csb");
	this->addChild(ui);
	this->scheduleUpdate();
	//从ui中加载按钮
	m_closeBtn = (Button*)ui->getChildByName("Button_x");
	m_collectBtn = (Button*)ui->getChildByName("Button_collect");
	m_cardEnhanceTime = (Text*)ui->getChildByName("time_Collection");
	if (CardManager::getInstance()->getCardEnhanced() != nullptr)
	{
		m_isCollectionContainsCard = true;
	}
	else
	{
		m_isCollectionContainsCard = false;
	}
	if (CardManager::getInstance()->getCardsFromEnhancer().size() > 0)
		m_isEnhancerContaninsACard = true;
	else
		m_isEnhancerContaninsACard = false;

	if (DataManager::getInstance()->getStartDate() > 0 && DataManager::getInstance()->getEndingDate() > 0)
	{
		if (m_currentTime >= DataManager::getInstance()->getEndingDate())
		{
			m_isCardsStartEnhance = false;
			TimeManager::getInstance()->setCardTime(0);
		}
		else
		{
			TimeManager::getInstance()->setCardTime(DataManager::getInstance()->getEndingDate() - m_currentTime);
			m_isCardsStartEnhance = true;
		}
		TimeManager::getInstance()->startCardTimeCountDown();
	}

	// 如果卡片管理器还没有从数据中读入卡片，读入卡片并且设变量为已经读入
	if(!GameManager::getInstance()->getIsCardManagerInitialized())
	{
		CardManager::getInstance()->loadCardFromData();
		CardManager::getInstance()->SortCardMsg(m_deltaX);
		GameManager::getInstance()->setIsCardManagerInitialized(true);
	}
	
	showCards();
	
	//获取屏幕分辨率
	auto glView = Director::getInstance()->getOpenGLView();
	m_frameSize = glView->getFrameSize();
	//log("size=%f", m_frameSize.width);

	//触控监听
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CardControlLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(CardControlLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(CardControlLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	listener->setSwallowTouches(true);

	//增加卡片合成完成事件监听
	auto cardEnhanceSucceedListener = EventListenerCustom::create("CardEnhanceSucceed", CC_CALLBACK_1(CardControlLayer::cardEnhanceSucceedCallBack, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(cardEnhanceSucceedListener, this);

	m_closeBtn->addTouchEventListener(this, toucheventselector(CardControlLayer::onCloseBtnClick));
	m_collectBtn->addTouchEventListener(this, toucheventselector(CardControlLayer::onCollectBtnClick));
	return true;
}

int CardControlLayer::getTimeStamp()
{
	timeval tm;
	gettimeofday(&tm, NULL);
	log("stamp %ld", tm.tv_usec / 1000 + tm.tv_sec * 1000);
	log("stamo %ld", tm.tv_sec);
	return tm.tv_sec;    // 单位：秒
	//    return tm.tv_usec; // 单位：毫秒

}

time_t CardControlLayer::getCurrentTime()
{
	time_t t = time(NULL);
	/*tm* lt = localtime(&t);

	int year = lt->tm_year + 1900;  // 相对1900年的过去的年数
	int month = lt->tm_mon + 1;     // 1月份：为0

	int yday = lt->tm_yday;         // 年第几天：从1开始
	int mday = lt->tm_mday;         // 月第几天：从1开始
	int wday = lt->tm_wday;         // 周第几天：从1开始

	int hh = lt->tm_hour;           // 时
	int mm = lt->tm_min;            // 分
	int ss = lt->tm_sec;            // 秒

	log("%d %d\n", year, month);
	log("%d %d %d\n", yday, mday, wday);
	log("%d %d %d\n", hh, mm, ss);
	return lt;*/
	return t;
}

void CardControlLayer::collectEnhancedCard(Card* card)
{
	//////////////////////////////
	DataManager::getInstance()->pushBackACard(card->getCardinfo(), card->getCardLevel());
	DataManager::getInstance()->saveCardData();
}

void CardControlLayer::update(float dt)
{
	if (TimeManager::getInstance()->isCardTimeCountingDowm())
	{
		m_cardEnhanceTime->setVisible(true);
		TimeManager::getInstance()->update(dt);
		m_cardEnhanceTime->setText(StringUtils::format("%02d", (int)(TimeManager::getInstance()->getCardTime()) / 60) + ":" 
			+ StringUtils::format("%02d", (int)(TimeManager::getInstance()->getCardTime()) % 60));
	}
	else
	{
		m_cardEnhanceTime->setVisible(false);
	}
}

void CardControlLayer::DeleteACard(Card* card)
{
	card->removeFromParent();
	CardManager::getInstance()->DeleteCardByObject(card,m_deltaX);
}

void CardControlLayer::DeleteAcardFromEnhancer(Card* card)
{
	card->removeFromParent();
	CardManager::getInstance()->DeleteCardByObjectFromEnhancer(card, m_deltaX);
}

void CardControlLayer::MoveCardIntoEnhancer(Card* card)
{
	
	if (card->getPosition().x >= (CARD_SLOT_X1 - 50)
		&& card->getPosition().x <= (CARD_SLOT_X1 + 50))
		card->setPosition(CARD_SLOT_X1, CARD_SLOT_Y);
	else if (card->getPosition().x >= (CARD_SLOT_X2 - 50)
		&& card->getPosition().x <= (CARD_SLOT_X2 + 50))
		card->setPosition(CARD_SLOT_X2, CARD_SLOT_Y);
	else
		return;
	CardManager::getInstance()->InsertACardIntoEnhancer(card);
	CardManager::getInstance()->DeleteCardByObject(card,m_deltaX);
	if (CardManager::getInstance()->getAllCards().size() <= m_frameSize.width / 80)
		CardManager::getInstance()->SortCardMsg();
	else if (CardManager::getInstance()->getAllCards().at(CardManager::getInstance()->getAllCards().size() - 1)->getPosition().x < m_frameSize.width - 60)
	{
		m_deltaX += 80;
		CardManager::getInstance()->SortCardMsg(m_deltaX);
	}
	/*if (!m_isEnhancerContaninsACard)
		CardManager::getInstance()->SortCardMsg(m_deltaX + 80);
	else
		CardManager::getInstance()->SortCardMsg(m_deltaX + 160);*/
}

void CardControlLayer::showCards()
{
	for (auto card : CardManager::getInstance()->getAllCards())
	{
		this->addChild(card);
//		log("if: %d, pos: %f, %f", card->getCardinfo(), card->getPositionX(), card->getPositionY());
	}
	for (auto card : CardManager::getInstance()->getCardsFromEnhancer())
	{
		this->addChild(card);
		log("if %d", card->getCardinfo());
	}
	if (CardManager::getInstance()->getCardEnhanced() != nullptr)
		this->addChild(CardManager::getInstance()->getCardEnhanced());
}

void CardControlLayer::ClickCardBackToBottom(Card* card)
{
	CardManager::getInstance()->InsertACard(card);
	//把卡片合成器中的卡片移动回下方的卡片容器
	if (card->getPosition().y == 300)
	{
		/*if (CardManager::getInstance()->getAllCards().at(CardManager::getInstance()->getAllCards().size() - 1)->getPosition().x < m_frameSize.width - 60)
			m_deltaX -= 80;*/
		CardManager::getInstance()->DeleteCardByObjectFromEnhancer(card, m_deltaX);
	}
	else//把中间位置合成后的卡片移进容器
	{
		CardManager::getInstance()->DeleteCardByObjectAfterCollection(card, m_deltaX);
		//m_sprite->setVisible(false);
	}
/*
	if (CardManager::getInstance()->getCardEnhanced() == nullptr)
		m_isCollectionContainsCard = false;
*/
	if (CardManager::getInstance()->getCardsFromEnhancer().size() == 0)
		m_isEnhancerContaninsACard = false;
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

bool CardControlLayer::IsSingleInVector(Card* card)
{
	/*bool temp1 = true;
	bool temp = true;
	for (auto tempCard : CardManager::getInstance()->getAllCards())
	{
		if (card->getCardLevel() == tempCard->getCardLevel()
			&& card->getCardinfo() == tempCard->getCardinfo())
		{
			if (tempCard->getPosition().x <= (card->getPosition().x + 40)
				&& tempCard->getPosition().x >= (card->getPosition().x - 40))
			{
				temp1 = true;
			}
			else
			{
				temp1 = false;
				break;
			}
		}
	}
	return temp;*/
	int num = 0;
	for (auto tempCard : CardManager::getInstance()->getAllCards())
	{
		if (card->getCardLevel() == tempCard->getCardLevel()
			&& card->getCardinfo() == tempCard->getCardinfo())
			num += 1;
		else
			continue;
	}
	for (auto tempCard : CardManager::getInstance()->getCardsFromEnhancer())
	{
		if (card->getCardLevel() == tempCard->getCardLevel()
			&& card->getCardinfo() == tempCard->getCardinfo())
			num += 1;
		else
			continue;
	}
	if (num < 2)
		return true;
	else
		return false;
}

void CardControlLayer::CardEnhanceSucceed()
{
	m_isCollectionContainsCard = true;
	m_isCardsStartEnhance = false;
	Card * tempCard = nullptr;
	for (auto card : CardManager::getInstance()->getCardsFromEnhancer())
	{
		tempCard = card;
		break;
	}
	if (tempCard != nullptr)
	{
		auto card = CardManager::getInstance()->CreateACardByTypeAndLevel(tempCard->getCardinfo(), (tempCard->getCardLevel() + 1), 350);
		this->addChild(card);
		//for (auto card : CardManager::getInstance()->getCardAfterCollection());
	}
	for (auto card : CardManager::getInstance()->getCardsFromEnhancer())
	{
		DeleteAcardFromEnhancer(card);
	}
	//m_sprite->setVisible(true);
	//DataManager::getInstance()->setEndingTimeStamp(0);
	//DataManager::getInstance()->setStartTimeStamp(0);
	DataManager::getInstance()->setStartDate(0);
	DataManager::getInstance()->setEndingDate(0);
	m_cardEnhanceTime->setVisible(false);
}

void CardControlLayer::cardEnhanceSucceedCallBack(cocos2d::EventCustom * cardEvent)
{
	std::string * cardCollection = (std::string*)cardEvent->getUserData();
	CCLOG("card Collection: %s", cardCollection);
	TimeManager::getInstance()->pauseCardTimeCountingDown();
	CardEnhanceSucceed();
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
	if (!m_isCardsStartEnhance && CardManager::getInstance()->getCardsFromEnhancer().size() == 2)
	{
		Card * cardTemp = nullptr;
		for (auto card : CardManager::getInstance()->getCardsFromEnhancer())
		{
			cardTemp = card;
			break;
		}
		m_isCardsStartEnhance = true;
		TimeManager::getInstance()->setCardTime(cardTemp->getCardLevel() * 60);
		log("cardtime %f", TimeManager::getInstance()->getCardTime());
		TimeManager::getInstance()->startCardTimeCountDown();
		/*DataManager::getInstance()->setStartTimeStamp(getTimeStamp());
		DataManager::getInstance()->setEndingTimeStamp(
			DataManager::getInstance()->getEndingTimeStamp() + cardTemp->getCardLevel() * 10);*/
		DataManager::getInstance()->setStartDate(getCurrentTime());
		DataManager::getInstance()->setEndingDate(
			DataManager::getInstance()->getStartDate() + cardTemp->getCardLevel() * 60);

	}
	else if(!m_isCardsStartEnhance)
	{
		
	}
}

bool CardControlLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	m_beginPos = touch->getLocation();
	log("x=%f", m_beginPos.x);
	// 通过点击的方式从合成器中吧卡片移回下方容器
	if (m_isCardsStartEnhance == false)
	{
		for (auto card : CardManager::getInstance()->getCardsFromEnhancer())
		{
			if (card->getBoundingBox().containsPoint(m_beginPos))
			{
				if (CardManager::getInstance()->getCardsFromEnhancer().size() > 0)
					ClickCardBackToBottom(card);
				else
					m_isEnhancerContaninsACard = false;
			}
		}
	}
	// 通过点击的方式吧合成的卡片移进下方容器
	auto card = CardManager::getInstance()->getCardEnhanced();
	if (card != nullptr && card->getBoundingBox().containsPoint(m_beginPos))
	{
		ClickCardBackToBottom(card);
	}
	else
	{
		m_isCollectionContainsCard = false;
	}
/*	for(auto card : CardManager::getInstance()->getCardsFromEnhancer())
	{
		if(card->getBoundingBox().containsPoint(m_beginPos))
		{
			ClickCardBackToBottom(
		}
	}*/
	for (auto card : CardManager::getInstance()->getAllCards())
	{
		if (card->getBoundingBox().containsPoint(m_beginPos))
		{
			m_isSingleCard = IsSingleInVector(card);
		}
	}
	return true;
}

void CardControlLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	Rect rect;
	m_delta = touch->getDelta();
	m_movedPos = touch->getLocation();
	/*auto cardBegin = CardManager::getInstance()->getAllCards().at(0);
	auto cardEnd = CardManager::getInstance()->getAllCards().at(CardManager::getInstance()->getAllCards().size()-1);*/
	// 卡片滑动
	// 当滑动x轴距离大于10时才开始滑动，当点击开始点和目前点y轴大于80时不能滑动
	if (m_operatingCard == nullptr && abs(m_beginPos.x - m_movedPos.x) >= 10 && m_movedPos.y <= 80 && m_beginPos.y <= 80)
	{
		if (CardManager::getInstance()->getAllCards().size() >= m_frameSize.width / 80)
		{
			if (CardManager::getInstance()->getAllCards().at(0)->getPosition().x <= 20
				&& CardManager::getInstance()->getAllCards().at(CardManager::getInstance()->getAllCards().size() - 1)->getPosition().x >= (m_frameSize.width - 100))
			{
				for (auto card : CardManager::getInstance()->getAllCards())
				{
					auto pos = card->getPosition();
					card->setPosition(pos.x + m_delta.x, 0);

				}
				log("%f----%f", m_delta.x, m_deltaX);
				m_deltaX += m_delta.x;
			}
			else if (CardManager::getInstance()->getAllCards().at(0)->getPosition().x > 20
				&& CardManager::getInstance()->getAllCards().at(CardManager::getInstance()->getAllCards().size() - 1)->getPosition().x >= (m_frameSize.width - 100))
			{
				if (m_delta.x < 0)
				{
					for (auto card : CardManager::getInstance()->getAllCards())
					{
						auto pos = card->getPosition();
						card->setPosition(pos.x + m_delta.x, 0);

					}
					log("%f----%f", m_delta.x, m_deltaX);
					m_deltaX += m_delta.x;
				}
			}
			else if (CardManager::getInstance()->getAllCards().at(0)->getPosition().x <= 20
				&& CardManager::getInstance()->getAllCards().at(CardManager::getInstance()->getAllCards().size() - 1)->getPosition().x < (m_frameSize.width - 100))
			{
				if (m_delta.x > 0)
				{
					for (auto card : CardManager::getInstance()->getAllCards())
					{
						auto pos = card->getPosition();
						card->setPosition(pos.x + m_delta.x, 0);

					}
					log("%f----%f", m_delta.x, m_deltaX);
					m_deltaX += m_delta.x;
				}
			}
			/*else if (CardManager::getInstance()->getAllCards().at(0)->getPosition().x > 20)
			{
				m_deltaX -= 5;
				CardManager::getInstance()->SortCardMsg(m_deltaX);
			}
			else if (CardManager::getInstance()->getAllCards().at(CardManager::getInstance()->getAllCards().size() - 1)->getPosition().x < (m_frameSize.width - 100))
			{
				m_deltaX += 5;
				CardManager::getInstance()->SortCardMsg(m_deltaX);
			}*/
		}
	}
	// 把卡片移动到卡片管理器
	else if ((m_isCollectionContainsCard == false) && (m_isCardsStartEnhance == false))//在卡片没有卡片在已经合成并且还在合成后预览位置时
	{
		//当前触点位置和点击初始位置的y轴距离绝对值大于40并且卡片合成器中卡片张数少于2，同时当前没有正在移动的卡片
		if (abs(m_movedPos.y - m_beginPos.y) >= 30)
		{
			Vec2 cardPos;
			cardPos.x = m_movedPos.x;
			cardPos.y = m_beginPos.y;
			if (CardManager::getInstance()->getCardsFromEnhancer().size() < 2)
			{
				if (m_operatingCard == nullptr)
				{
					for (auto card : CardManager::getInstance()->getAllCards())
					{
						if (/*card->getBoundingBox().containsPoint(m_beginPos)*/card->getBoundingBox().containsPoint(cardPos) && !m_isSingleCard)
						{
							m_operatingCard = card;
							m_operatingCard->setPosition(m_movedPos.x - 40, m_movedPos.y - 40);
							break;
							/*if (m_isSingleCard)
							{
								m_operatingCard = nullptr;
								continue;
							}
							else
							{
								m_operatingCard->setPosition(m_movedPos.x - 40, m_movedPos.y - 40);
								break;
							}*/
						}
					}
					/*if (m_operatingCard != nullptr)
					{
						for (auto card : CardManager::getInstance()->getAllCards())
						{
							if (CardManager::getInstance()->getCardsFromEnhancer().size() == 0)
							{
								m_isSingleCard = IsSingleInVector(m_operatingCard);
							}
							if (CardManager::getInstance()->getCardsFromEnhancer().size() == 1)
							{
								if (IsTheSameCardInEnhancer(m_operatingCard))
									m_isSingleCard = false;
								else
								{
									m_operatingCard = nullptr;
									break;
								}
							}
							else
								continue;
						}
					}
					if (m_isSingleCard)
					{
						m_operatingCard = nullptr;
						CardManager::getInstance()->SortCardMsg(m_deltaX);
					}*/
				}
			}

		}
		if (m_operatingCard != nullptr && m_isSingleCard == false)
		{
			m_operatingCard->setPosition(m_movedPos.x - 40, m_movedPos.y - 40);
		}
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
		if (m_isEnhancerContaninsACard)
		{
			if (IsTheSameCardInEnhancer(m_operatingCard))
			{
				for (auto card : CardManager::getInstance()->getCardsFromEnhancer())
				{
					// 如果要移进的卡片合成器的位置上已经有一张卡片
					if (m_operatingCard->getPosition().x >= (card->getPosition().x - 50)
						&& m_operatingCard->getPosition().x <= (card->getPosition().x + 50))
					{
						m_operatingCard = nullptr;
						CardManager::getInstance()->SortCardMsg(m_deltaX);
						break;
					}
					else
					{
						MoveCardIntoEnhancer(m_operatingCard);
						m_operatingCard = nullptr;
					}
				}
			}
			else
			{
				m_operatingCard = nullptr;
				CardManager::getInstance()->SortCardMsg(m_deltaX+80);
			}
		}
		else
		{
			MoveCardIntoEnhancer(m_operatingCard);
			m_operatingCard = nullptr;
			m_isEnhancerContaninsACard = true;

		}
	}
	else
	{
		m_operatingCard = nullptr;
		CardManager::getInstance()->SortCardMsg(m_deltaX);
	}
	/*if (CardManager::getInstance()->getAllCards().at(CardManager::getInstance()->getAllCards().size() - 1)->getPosition().x <= m_frameSize.width - 100)
		CardManager::getInstance()->SortCardMsg(m_deltaX + 80);*/
	m_isSingleCard = true;
}