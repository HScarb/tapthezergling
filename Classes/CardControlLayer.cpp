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
	//��ui�м��ذ�ť
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

	// �����Ƭ��������û�д������ж��뿨Ƭ�����뿨Ƭ���������Ϊ�Ѿ�����
	if(!GameManager::getInstance()->getIsCardManagerInitialized())
	{
		CardManager::getInstance()->loadCardFromData();
		CardManager::getInstance()->SortCardMsg(m_deltaX);
		GameManager::getInstance()->setIsCardManagerInitialized(true);
	}
	
	showCards();
	
	//��ȡ��Ļ�ֱ���
	auto glView = Director::getInstance()->getOpenGLView();
	m_frameSize = glView->getFrameSize();
	//log("size=%f", m_frameSize.width);

	//���ؼ���
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CardControlLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(CardControlLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(CardControlLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	listener->setSwallowTouches(true);

	//���ӿ�Ƭ�ϳ�����¼�����
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
	return tm.tv_sec;    // ��λ����
	//    return tm.tv_usec; // ��λ������

}

time_t CardControlLayer::getCurrentTime()
{
	time_t t = time(NULL);
	/*tm* lt = localtime(&t);

	int year = lt->tm_year + 1900;  // ���1900��Ĺ�ȥ������
	int month = lt->tm_mon + 1;     // 1�·ݣ�Ϊ0

	int yday = lt->tm_yday;         // ��ڼ��죺��1��ʼ
	int mday = lt->tm_mday;         // �µڼ��죺��1��ʼ
	int wday = lt->tm_wday;         // �ܵڼ��죺��1��ʼ

	int hh = lt->tm_hour;           // ʱ
	int mm = lt->tm_min;            // ��
	int ss = lt->tm_sec;            // ��

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
	//�ѿ�Ƭ�ϳ����еĿ�Ƭ�ƶ����·��Ŀ�Ƭ����
	if (card->getPosition().y == 300)
	{
		/*if (CardManager::getInstance()->getAllCards().at(CardManager::getInstance()->getAllCards().size() - 1)->getPosition().x < m_frameSize.width - 60)
			m_deltaX -= 80;*/
		CardManager::getInstance()->DeleteCardByObjectFromEnhancer(card, m_deltaX);
	}
	else//���м�λ�úϳɺ�Ŀ�Ƭ�ƽ�����
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
	// ͨ������ķ�ʽ�Ӻϳ����аɿ�Ƭ�ƻ��·�����
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
	// ͨ������ķ�ʽ�ɺϳɵĿ�Ƭ�ƽ��·�����
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
	// ��Ƭ����
	// ������x��������10ʱ�ſ�ʼ�������������ʼ���Ŀǰ��y�����80ʱ���ܻ���
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
	// �ѿ�Ƭ�ƶ�����Ƭ������
	else if ((m_isCollectionContainsCard == false) && (m_isCardsStartEnhance == false))//�ڿ�Ƭû�п�Ƭ���Ѿ��ϳɲ��һ��ںϳɺ�Ԥ��λ��ʱ
	{
		//��ǰ����λ�ú͵����ʼλ�õ�y��������ֵ����40���ҿ�Ƭ�ϳ����п�Ƭ��������2��ͬʱ��ǰû�������ƶ��Ŀ�Ƭ
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

	// ���ֻ�ǻ�����û�в�����Ƭ���ж��Ƿ��ǵ����Ƭ��ʾ��Ƭ��Ϣ
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

	// �����Ƭ�ƶ����յ��ڿ�Ƭ�ϳ������۸����ķ�Χ���ǾͰѿ�Ƭֱ���ƶ�������
	// �����Ƭ�ƶ��յ�����y�᷶Χ��[300,400],x��������[300,400]����[600,700]ʱ
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
					// ���Ҫ�ƽ��Ŀ�Ƭ�ϳ�����λ�����Ѿ���һ�ſ�Ƭ
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