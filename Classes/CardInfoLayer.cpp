//CardInfoLayer.cpp
#include "CardInfoLayer.h"
#include "cocostudio/CocoStudio.h"
#include "CardManager.h"

USING_NS_CC;
using namespace cocos2d::ui;


cocos2d::Scene* CardInfoLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = CardInfoLayer::create();
	scene->addChild(scene);
	return scene;
}

bool CardInfoLayer::init()
{
	if (!Layer::init())
		return false;
	m_closeBtn = nullptr;
	m_cardInfo = nullptr;
	m_cardName = nullptr;

	auto ui = CSLoader::createNode("CardInfoLayer.csb");
	this->addChild(ui);

	m_closeBtn = (Button *)ui->getChildByName("btnClose");

	m_cardInfo = (Text*)ui->getChildByName("cardInfo");
	m_cardName = (Text*)ui->getChildByName("cardName");
	//´¥¿Ø¼àÌý
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CardInfoLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	listener->setSwallowTouches(true);
	m_closeBtn->addTouchEventListener(this, toucheventselector(CardInfoLayer::onCloseBtnClick));
	return true;
}

bool CardInfoLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	log("111");
	return true;
}

void CardInfoLayer::onCloseBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	this->removeFromParent();
}