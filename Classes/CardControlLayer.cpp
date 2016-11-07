//CardControlLayer.cpp
#include"CardControlLayer.h"
#include "cocostudio/CocoStudio.h"
#include "CardManager.h"

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
	/*m_noTouchLayer = nullptr;#i*/
	
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
	if (m_CardMsg.size() == 0)
	{
		//创建卡片
		for (int i = 15; i >= 1; i--)
		{
			if (i > 10)
			{
				CreateACard(i-10, 1, i - 1);
			}
			else
				CreateACard(i, 1, i - 1);
		}
	}

	//CardManager::getInstance()->DeleteCardByTypeAndLevel(5, 1);
	CardManager::getInstance()->SortCardMsg();;

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
	card->removeFromParent();
	CardManager::getInstance()->DeleteCardByTypeAndLevel(card->getCardinfo(), card->getCardLevel());
	CardManager::getInstance()->SortCardMsg();
}

void CardControlLayer::onCloseBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		/*unShowLayer();*/
		this->removeFromParent();
	}
}
void CardControlLayer::onCollectBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	
}

/*void CardControlLayer::showLayer()
{
	// 创建一个无触摸层，在卡片控制层的下面
	m_noTouchLayer = NoTouchLayer::create();
	this->addChild(m_noTouchLayer, 0);
	// 显示卡片控制层
	this->setVisible(true);
}

void CardControlLayer::unShowLayer()
{
	// 移除无触摸层
	this->removeChild(m_noTouchLayer);
	// 隐藏卡片控制层
	this->setVisible(false);
}*/

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

void CardControlLayer::moveCards(float delta)
{
	CardManager::getInstance()->MoveCards(delta);
}

bool CardControlLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	
	m_Bpos = touch->getLocation();
	log("x=%f",m_Bpos.x);

	for (auto card : CardManager::getInstance()->getAllCards())
	{
		auto pos = card->getPosition();
		card->setPosition(pos.x + 10, 0);
	}
	return true;
}

void CardControlLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	m_delta = touch->getDelta();
	m_Mpos = touch->getLocation();
	/*if (abs(m_Bpos.x - m_Mpos.x) >= 10)
	{

	}*/
	MoveTo *moveto = nullptr;
	for (auto card : CardManager::getInstance()->getAllCards())
	{
		auto pos = card->getPosition();
		card->setPosition(pos.x + m_delta.x, 0);
		/*if (card->getCardinfo() == 5)
			card->setPosition(300,300);*/
		moveto = MoveTo::create(0.1f, Point(pos.x + m_delta.x,0));
		if (moveto)
			card->runAction(moveto);
	}
	//moveCards(m_delta.x);
}

void CardControlLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	Rect rect;
	if (m_Bpos.y <= 80)
	{
		m_Epos = touch->getLocation();
		if (abs(m_Bpos.x - m_Epos.x) < 10)
		{
			auto cards = CardManager::getInstance()->getAllCards();
			int i = 0;
			for (auto card : cards)
			{
				rect = card->getBoundingBox();

				if (rect.containsPoint(m_Epos))
				{
					log("info=%d local x=%f,y=%f", card->getCardinfo(), card->getPosition().x, card->getPosition().y);
					DeleteACard(card);
					/*m_cardInfoLayer = CardInfoLayer::create();
					this->addChild(m_cardInfoLayer);*/
					break;
				}
				i++;
			}
		}
	}
	log("delta %f", abs(m_Bpos.x - m_Epos.x));
	auto cards = CardManager::getInstance()->getAllCards();
	for (auto card : cards)
	{
		log("info %d,pos=%f", card->getCardinfo(), card->getPosition().x);
	}
}