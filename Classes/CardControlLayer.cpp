//CardControlLayer.cpp
#include"CardControlLayer.h"
#include "cocostudio/CocoStudio.h"
#include "CardManager.h"
#include "TimeManager.h"
#include "DataManager.h"
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
	m_currentTime = getCurrentTime();
	m_timeStamp=getTimeStamp();
	log("cardtime %d,et %d", DataManager::getInstance()->getStartTimeStamp(), DataManager::getInstance()->getEndingTimeStamp());
	m_collectBtn = nullptr;
	m_closeBtn = nullptr;
	m_operatingCard = nullptr;
	m_isCardsStartCollection = false;
	m_isSingleCard = true;
	m_cardCollectionTime = nullptr;
	auto ui = CSLoader::createNode("CardEnhancer.csb");
	this->addChild(ui);
	this->scheduleUpdate();
	//��ui�м��ذ�ť
	m_closeBtn = (Button *)ui->getChildByName("Button_x");
	m_collectBtn = (Button *)ui->getChildByName("Button_collect");
	m_cardCollectionTime = (Text*)ui->getChildByName("time_Collection");
	//m_sprite = (ImageView*)ui->getChildByName("imageCollection");
	if (CardManager::getInstance()->getCardAfterCollection().size() > 0)
	{
		m_isCollectionContainsCard = true;
		//m_sprite->setVisible(true);
	}	
	else
	{
		m_isCollectionContainsCard = false;
		//m_sprite->setVisible(false);
	}
	if (CardManager::getInstance()->getCardsFromEnhancer().size() > 0)
		m_isEnhancerContaninsACard = true;
	else
		m_isEnhancerContaninsACard = false;

	if (DataManager::getInstance()->getStartTimeStamp() > 0 && DataManager::getInstance()->getEndingTimeStamp() > 0)
	{
		if (m_timeStamp >= DataManager::getInstance()->getEndingTimeStamp())
		{
			m_isCardsStartCollection = false;
			TimeManager::getInstance()->setCardTime(0);
		}
		else
		{
			TimeManager::getInstance()->setCardTime(DataManager::getInstance()->getEndingTimeStamp() - m_timeStamp);
			m_isCardsStartCollection = true;
		}
		TimeManager::getInstance()->startCardTimeCountDown();
	}
	if (CardManager::getInstance()->getAllCards().size() == 0)
	{
		//������Ƭ
		for (int i = 25; i >= 1; i--)
		{
			/*if (i > 10)
			{
				auto card = CardManager::getInstance()->CreateACardByTypeAndLevel((Card::CardInfo)(random(1,10)), 1, i - 1);
				this->addChild(card);
			}
			else
			{
				auto card = CardManager::getInstance()->CreateACardByTypeAndLevel((Card::CardInfo)1, 1, i - 1);
				this->addChild(card);
			}*/
			auto card = CardManager::getInstance()->CreateACardByTypeAndLevel((Card::CardInfo)(random(1, 10)), 1, 1);
			this->addChild(card);
		}
	}
	else
		showCards();
	CardManager::getInstance()->SortCardMsg();

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
	auto cardCollectionListener = EventListenerCustom::create("CardCollectionSucceed", CC_CALLBACK_1(CardControlLayer::cardCollectionSucceedCallBack, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(cardCollectionListener,this);

	m_closeBtn->addTouchEventListener(this, toucheventselector(CardControlLayer::onCloseBtnClick));
	m_collectBtn->addTouchEventListener(this, toucheventselector(CardControlLayer::onCollectBtnClick));
	return true;
}

int CardControlLayer::getTimeStamp()
{
	timeval tm;
	gettimeofday(&tm, NULL);
	log("stamp %ld", tm.tv_usec/1000+tm.tv_sec*1000);
	log("stamo %ld", tm.tv_sec);
	return tm.tv_sec;    // ��λ����
	//    return tm.tv_usec; // ��λ������
	
}

tm* CardControlLayer::getCurrentTime()
{
	time_t t = time(NULL);
	tm* lt = localtime(&t);

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
	return lt;
}

void CardControlLayer::update(float dt)
{
	if (TimeManager::getInstance()->isCardTimeCountingDowm())
	{
		TimeManager::getInstance()->update(dt);
		m_cardCollectionTime->setText(StringUtils::format("%05.2f", TimeManager::getInstance()->getCardTime()));
	}
}

void CardControlLayer::DeleteACard(Card* card)
{
	card->removeFromParent();
	CardManager::getInstance()->DeleteCardByObject(card);
}

void CardControlLayer::DeleteAcardFromEnhancer(Card* card)
{
	card->removeFromParent();
	CardManager::getInstance()->DeleteCardByObjectFromEnhancer(card);
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
	CardManager::getInstance()->DeleteCardByObject(card);
}

void CardControlLayer::showCards()
{
	for (auto card : CardManager::getInstance()->getAllCards())
	{
		//auto tempCard = CardManager::getInstance()->CreateACardByTypeAndLevel(card);
		this->addChild(card);
		log("if %d", card->getCardinfo());
	}
	for (auto card : CardManager::getInstance()->getCardsFromEnhancer())
	{
		//auto tempCard = CardManager::getInstance()->CreateACardByTypeAndLevel(card);
		this->addChild(card);
		log("if %d", card->getCardinfo());
	}
	for (auto card : CardManager::getInstance()->getCardAfterCollection())
	{
		//auto tempCard = CardManager::getInstance()->CreateACardByTypeAndLevel(card);
		this->addChild(card);
		log("if %d", card->getCardinfo());
	}
}

void CardControlLayer::ClickCardBackToBottom(Card* card)
{
	CardManager::getInstance()->InsertACard(card);
	//�ѿ�Ƭ�ϳ����еĿ�Ƭ�ƶ����·��Ŀ�Ƭ����
	if (card->getPosition().y == 300)
		CardManager::getInstance()->DeleteCardByObjectFromEnhancer(card);
	else//���м�λ�úϳɺ�Ŀ�Ƭ�ƽ�����
	{
		CardManager::getInstance()->DeleteCardByObjectAfterCollection(card);
		//m_sprite->setVisible(false);
	}
	if (CardManager::getInstance()->getCardAfterCollection().size() == 0)
		m_isCollectionContainsCard = false;
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
	bool temp = true;
	for (auto tempCard : CardManager::getInstance()->getAllCards())
	{
		if (card->getCardLevel() == tempCard->getCardLevel()
			&& card->getCardinfo() == tempCard->getCardinfo())
		{
			if (tempCard->getPosition().x <= (card->getPosition().x + 40)
				&& tempCard->getPosition().x >= (card->getPosition().x - 40))
			{
				temp = true;
			}
			else
			{
				temp = false;
				break;
			}
		}
	}
	return temp;
}

void CardControlLayer::CardCollectionSucceed()
{
	m_isCollectionContainsCard = true;
	m_isCardsStartCollection = false;
	Card * tempCard = nullptr;
	for (auto card : CardManager::getInstance()->getCardsFromEnhancer())
	{
		tempCard = card;
		break;
	}
	if (tempCard != nullptr)
	{
		auto card = CardManager::getInstance()->CreateACardByTypeAndLevel((Card::CardInfo)tempCard->getCardinfo(), (tempCard->getCardLevel() + 1), 450);
		this->addChild(card);
		for (auto card : CardManager::getInstance()->getCardAfterCollection());
	}
	for (auto card : CardManager::getInstance()->getCardsFromEnhancer())
	{
		DeleteAcardFromEnhancer(card);
	}
	//m_sprite->setVisible(true);
	DataManager::getInstance()->setEndingTimeStamp(0);
	DataManager::getInstance()->setStartTimeStamp(0);
	DataManager::getInstance()->setStartDate(nullptr);
}

void CardControlLayer::cardCollectionSucceedCallBack(cocos2d::EventCustom * cardEvent)
{
	std::string * cardCollection = (std::string*)cardEvent->getUserData();
	CCLOG("%s1111111111", cardCollection);
	TimeManager::getInstance()->pauseCardTimeCountingDown();
	CardCollectionSucceed();
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
	if (!m_isCardsStartCollection&&CardManager::getInstance()->getCardsFromEnhancer().size()==2)
	{
		Card * cardTemp = nullptr;
		for (auto card : CardManager::getInstance()->getCardsFromEnhancer())
		{
			cardTemp = card;
			break;
		}
		m_isCardsStartCollection = true;
		TimeManager::getInstance()->setCardTime((cardTemp->getCardLevel()*10));
		log("cardtime %f", TimeManager::getInstance()->getCardTime());
		TimeManager::getInstance()->startCardTimeCountDown();
		DataManager::getInstance()->setStartTimeStamp(getTimeStamp());
		DataManager::getInstance()->setEndingTimeStamp(
			DataManager::getInstance()->getEndingTimeStamp() + cardTemp->getCardLevel() * 10);
		DataManager::getInstance()->setStartDate(getCurrentTime());
	}
	
	
}

bool CardControlLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	
	m_beginPos = touch->getLocation();
	log("x=%f",m_beginPos.x);
	//ͨ������ķ�ʽ�Ӻϳ����аɿ�Ƭ�ƻ��·�����
	if (m_isCardsStartCollection == false)
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
	//ͨ������ķ�ʽ�ɺϳɵĿ�Ƭ�ƽ��·�����
	for (auto card : CardManager::getInstance()->getCardAfterCollection())
	{
		if (card->getBoundingBox().containsPoint(m_beginPos))
		{
			if (CardManager::getInstance()->getCardAfterCollection().size() > 0)
				ClickCardBackToBottom(card);
			else
				m_isCollectionContainsCard = false;
		}
	}
	return true;
}

void CardControlLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	Rect rect;
	m_delta = touch->getDelta();
	m_movedPos = touch->getLocation();
	// ��Ƭ����
	// ������x��������10ʱ�ſ�ʼ�������������ʼ���Ŀǰ��y�����80ʱ���ܻ���
	if (m_operatingCard == nullptr && abs(m_beginPos.x - m_movedPos.x) >= 10 && m_movedPos.y <= 80 && m_beginPos.y <= 80)
	{
		if (CardManager::getInstance()->getAllCards().size() >= m_frameSize.width / 80)
		{
			for (auto card : CardManager::getInstance()->getAllCards())
			{
				auto pos = card->getPosition();
				card->setPosition(pos.x + m_delta.x, 0);
			}
		}
	}
	// �ѿ�Ƭ�ƶ�����Ƭ������
	else if ((m_isCollectionContainsCard == false) && (m_isCardsStartCollection == false))//�ڿ�Ƭû�п�Ƭ���Ѿ��ϳɲ��һ��ںϳɺ�Ԥ��λ��ʱ
	{
		//��ǰ����λ�ú͵����ʼλ�õ�y��������ֵ����40���ҿ�Ƭ�ϳ����п�Ƭ��������2��ͬʱ��ǰû�������ƶ��Ŀ�Ƭ
		if (abs(m_movedPos.y - m_beginPos.y) >= 30 )
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
						if (/*card->getBoundingBox().containsPoint(m_beginPos)*/card->getBoundingBox().containsPoint(cardPos))
						{
							m_operatingCard = card;
							m_operatingCard->setPosition(m_movedPos.x - 40, m_movedPos.y - 40);
							break;
						}
					}
					if (m_operatingCard != nullptr)
					{
						for (auto card : CardManager::getInstance()->getAllCards())
						{
							if (CardManager::getInstance()->getCardsFromEnhancer().size() == 0)
							{
								m_isSingleCard = IsSingleInVector(m_operatingCard);
							}
							else if (CardManager::getInstance()->getCardsFromEnhancer().size() == 1)
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
						CardManager::getInstance()->SortCardMsg();
					}
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
					//���Ҫ�ƽ��Ŀ�Ƭ�ϳ�����λ�����Ѿ���һ�ſ�Ƭ
					if (m_operatingCard->getPosition().x >= (card->getPosition().x - 50)
						&& m_operatingCard->getPosition().x <= (card->getPosition().x + 50))
					{
						m_operatingCard = nullptr;
						CardManager::getInstance()->SortCardMsg();
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
				CardManager::getInstance()->SortCardMsg();
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
		CardManager::getInstance()->SortCardMsg();
	}
	m_isSingleCard = true;
}