//CardControlLayer.cpp
#include"CardControlLayer.h"
#include "cocostudio/CocoStudio.h"
#include "CardManager.h"
#include "TimeManager.h"
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
	m_isEnhancerContaninsACard = false;
	m_isCollectionContainsCard = false;
	m_isSingleCard = true;
	m_cardCollectionTime = nullptr;
	auto ui = CSLoader::createNode("CardEnhancer.csb");
	this->addChild(ui);
	//从ui中加载按钮
	m_closeBtn = (Button *)ui->getChildByName("Button_x");
	m_collectBtn = (Button *)ui->getChildByName("Button_collect");
	m_cardCollectionTime = (Text*)ui->getChildByName("time_Collection");
	if (CardManager::getInstance()->getAllCards().size() == 0)
	{
		//创建卡片
		for (int i = 9; i >= 1; i--)
		{
			if (i > 10)
			{
				CreateACard(i - 10, 1, i - 1);
			}
			else
				CreateACard(1, 1, i - 1);
		}
	}
	else
		showCards();

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

	//增加卡片合成完成事件监听
	auto cardCollectionListener = EventListenerCustom::create("CardCollectionSucceed", CC_CALLBACK_1(CardControlLayer::cardCollectionSucceedCallBack, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(cardCollectionListener,this);

	m_closeBtn->addTouchEventListener(this, toucheventselector(CardControlLayer::onCloseBtnClick));
	m_collectBtn->addTouchEventListener(this, toucheventselector(CardControlLayer::onCollectBtnClick));
	return true;

}

void CardControlLayer::update(float dt)
{
	if (TimeManager::getInstance()->isCardTimeCountingDowm())
	{
		TimeManager::getInstance()->update(dt);
		m_cardCollectionTime->setText(StringUtils::format("%05.2f", TimeManager::getInstance()->getCardTime()));
	}
}

void CardControlLayer::CreateACard(int info,int level,int posX)
{
	CardManager::getInstance()->InsertACard(CreateACardByTypeAndLevel(
		(Card::CardInfo)info, level, posX));
}

void CardControlLayer::DeleteACard(Card* card)
{
	card->removeFromParent();
	CardManager::getInstance()->DeleteCardByObject(card);
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

void CardControlLayer::onCloseBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		this->removeFromParent();
	}
}
void CardControlLayer::onCollectBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	ClickedToStartCollectCards();
	TimeManager::getInstance()->setCardTime(10);
	this->scheduleUpdate();
	m_isCollectionContainsCard = true;
}

Card* CardControlLayer::CreateACardByTypeAndLevel(Card::CardInfo info, int level,int posX)
{
	Card * card = nullptr;
	if (info == 0)
		return nullptr;
	card = Card::createByInfo(info);
	card->setCardLevel(level);//设置等级
	if (posX != 450)
		card->setPosition(posX * 80, 0);//设定新增卡片的坐标
	else
		card->setPosition(450, 350);//设定合成后的卡片的坐标
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
		this->addChild(card);
	for (auto card : CardManager::getInstance()->getCardAfterCollection())
		this->addChild(card);
}

void CardControlLayer::ClickCardBackToBottom(Card* card)
{
	CardManager::getInstance()->InsertACard(card);
	//把卡片合成器中的卡片移动回下方的卡片容器
	if (card->getPosition().y == 300)
		CardManager::getInstance()->DeleteCardByObjectFromEnhancer(card);
	else//把中间位置合成后的卡片移进容器
		CardManager::getInstance()->DeleteCardByObjectAfterCollection(card);
	if (CardManager::getInstance()->getCardAfterCollection().size() == 0)
		m_isCollectionContainsCard = false;
	if (CardManager::getInstance()->getCardsFromEnhancer().size() == 0)
		m_isEnhancerContaninsACard = false;
	for (auto card : CardManager::getInstance()->getAllCards())
	{
		log("Name %d,level %d", card->getCardinfo(), card->getCardLevel());
	}
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
	bool temp=true;
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

void CardControlLayer::ClickedToStartCollectCards()
{
	log("cardtime %f", TimeManager::getInstance()->getCardTime());
	TimeManager::getInstance()->startCardTimeCountDown();
}

void CardControlLayer::CardCollectionSucceed()
{
	Card * tempCard = nullptr;
	for (auto card : CardManager::getInstance()->getCardsFromEnhancer())
	{
		tempCard = card;
		break;
	}
	if (tempCard != nullptr)
	{
		CardManager::getInstance()->InsertCardAfterCollection(CreateACardByTypeAndLevel((Card::CardInfo)tempCard->getCardinfo(), (tempCard->getCardLevel() + 1), 450));
		for (auto card : CardManager::getInstance()->getCardAfterCollection());
	}
	for (auto card : CardManager::getInstance()->getCardsFromEnhancer())
	{
		card->removeFromParent();
		CardManager::getInstance()->DeleteCardByObjectFromEnhancer(card);
	}
}

void CardControlLayer::cardCollectionSucceedCallBack(cocos2d::EventCustom * cardEvent)
{
	std::string * cardCollection = (std::string*)cardEvent->getUserData();
	CCLOG("%s1111111111",cardCollection);
	TimeManager::getInstance()->pauseCountDown();

	CardCollectionSucceed();
}

bool CardControlLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	
	m_beginPos = touch->getLocation();
	log("x=%f",m_beginPos.x);
	//通过点击的方式从合成器中吧卡片移回下方容器
	for (auto card : CardManager::getInstance()->getCardsFromEnhancer())
	{
		if (card->getBoundingBox().containsPoint(m_beginPos))
		{
			log("11111");
			if (CardManager::getInstance()->getCardsFromEnhancer().size() > 0)
				ClickCardBackToBottom(card);
			else
				m_isEnhancerContaninsACard = false;
		}
	}
	//通过点击的方式吧合成的卡片移进下方容器
	for (auto card : CardManager::getInstance()->getCardAfterCollection())
	{
		if (card->getBoundingBox().containsPoint(m_beginPos))
		{
			log("222222");
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
	// 卡片滑动
	// 当滑动x轴距离大于10时才开始滑动，当点击开始点和目前点y轴大于80时不能滑动
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
	// 把卡片移动到卡片管理器
	if (m_isCollectionContainsCard == false)//在卡片没有卡片在已经合成并且还在合成后预览位置时
	{
		//当前触点位置和点击初始位置的y轴距离绝对值大于40并且卡片合成器中卡片张数少于2，同时当前没有正在移动的卡片
		if (abs(m_movedPos.y - m_beginPos.y) >= 40 && CardManager::getInstance()->getCardsFromEnhancer().size() < 2 && m_operatingCard == nullptr)
		{
			for (auto card : CardManager::getInstance()->getAllCards())
			{
				if (card->getBoundingBox().containsPoint(m_beginPos))
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
					//如果要移进的卡片合成器的位置上已经有一张卡片
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