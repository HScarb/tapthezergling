//CardInfoLayer.cpp
#include "CardInfoLayer.h"
#include "cocostudio/CocoStudio.h"
#include "CardManager.h"
#include "GlobalConst.h"

USING_NS_CC;
using namespace cocos2d::ui;


cocos2d::Scene* CardInfoLayer::createScene(int info, int level)
{
	auto scene = Scene::create();
	auto layer = CardInfoLayer::create(info, level);
	scene->addChild(scene);
	return scene;
}

CardInfoLayer* CardInfoLayer::create(int info, int level)
{
	auto bRet = new CardInfoLayer();
	if (bRet&&bRet->init(info, level))
	{
		bRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(bRet);
	}
	return bRet;
}

bool CardInfoLayer::init(int info, int level)
{
	if (!Layer::init())
		return false;
	m_closeBtn = nullptr;
	m_cardInfo = nullptr;
	m_cardName = nullptr;
	m_info = info;
	m_level = level;

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
	//ÏÔÊ¾¿¨Æ¬ÐÅÏ¢
	//auto NameAndLevel = "Card Name:" + CARD_NAME[m_info] + ",Card Level:" + StringUtils::format("%d",m_level);
	//NameAndLevel.append((char)m_level);
	m_cardName->setText("Card Name:" + CARD_NAME[m_info] + ",Card Level:" + StringUtils::format("%d", m_level));
	//m_cardName->setText(NameAndLevel);
	//log("%s", NameAndLevel);

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