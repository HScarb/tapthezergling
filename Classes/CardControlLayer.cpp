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
	m_noTouchLayer = nullptr;
	auto ui = CSLoader::createNode("CardEnhancer.csb");
	this->addChild(ui,1);

	//从ui中加载按钮
	m_closeBtn = (Button *)ui->getChildByName("Button_x");
	m_collectBtn = (Button *)ui->getChildByName("Button_collect");
	//从ui中加载卡片滑动视图
	m_cardView = (ScrollView *)ui->getChildByName("cardView");
	//加载manager里的卡片容器
	m_CardMsg = CardManager::getInstance()->getAllCards();
	if (m_CardMsg.size() == 0)
	{
		//创建卡片
		for (int i = 10; i >= 1; i--)
		{
			CreateACard(i, 1);
		}
	}
	CreateACard(5, 2);
	//CardManager::getInstance()->DeleteCardByTypeAndLevel(5, 1);
	CardManager::getInstance()->SortCardMsg();
	//显示卡片
	showCards();

	// 图片菜单项测试
	// 创建一个图片菜单项，第一个参数是本来的图片，第二个参数是按下后的图片，然后是一个回调函数，注意这个回调函数需要有一个参数
	MenuItemImage* testMenuItem = MenuItemImage::create("Res/Cards/Card_1.png", "Res/Cards/Card_2.png", CC_CALLBACK_1(CardControlLayer::testMenuEvent, this));
	// 创建菜单，这里可以把多个菜单向放入一个菜单，用create即可 create(testMenuItem, item2, item3, NULL) 注意用NULL结尾
	Menu* p_menu = Menu::createWithItem(testMenuItem);
	// 将菜单加入ScrollView
	m_cardView->addChild(p_menu);

	//触控监听
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CardControlLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(CardControlLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	m_closeBtn->addTouchEventListener(this, toucheventselector(CardControlLayer::onCloseBtnClick));
	m_collectBtn->addTouchEventListener(this, toucheventselector(CardControlLayer::onCollectBtnClick));
	return true;

}

void CardControlLayer::CreateACard(int info,int level)
{
	CardManager::getInstance()->InsertACard(CreateACardByTypeAndLevel(
		(Card::CardInfo)info, level));
}

void CardControlLayer::DeleteACard(Card* card)
{
	card->removeFromParent();
	CardManager::getInstance()->DeleteCardByTypeAndLevel(card->getCardinfo(), card->getCardLevel());
}

void CardControlLayer::onCloseBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		unShowLayer();
	}
}
void CardControlLayer::onCollectBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	
}

void CardControlLayer::showLayer()
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
}

Card* CardControlLayer::CreateACardByTypeAndLevel(Card::CardInfo info, int level)
{
	Card * card = nullptr;
	if (info == 0)
		return nullptr;
	card = Card::createByInfo(info);
	card->setCardLevel(level);			//设置等级
	return card;
}

void CardControlLayer::showCards()
{
	auto cards = CardManager::getInstance()->getAllCards();
	int i = 0;
	for (auto card : cards)
	{
		if (card->getCardinfo() == 5 && card->getCardLevel() == 1)
		{
			DeleteACard(card);
			continue;
		}
		card = CreateACardByTypeAndLevel((Card::CardInfo)card->getCardinfo(), card->getCardLevel());
		log("Card Type %d,Card Level %d", card->getCardinfo(), card->getCardLevel());
		card->setPosition(i * 80, 200);
		m_cardView->addChild(card);
		i++;
	}
}

bool CardControlLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
/*	auto cards = CardManager::getInstance()->getAllCards();
	Rect rect;
	int i;
	for (auto card : cards)
	{
		rect = card->getBoundingBox();
		i = card->getCardinfo();
		auto pos = touch->getLocation();
		if (rect.containsPoint(pos))
		{
			log("cardtype%d", i);
		}
	}
	log("12345");*/
	return true;
}

void CardControlLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	
}

void CardControlLayer::testMenuEvent(Ref * sender)
{
	log("Menu touched");
}