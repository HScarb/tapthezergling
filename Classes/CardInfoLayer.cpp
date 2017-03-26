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
	scene->addChild(layer);
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
	m_cardLevel = nullptr;
	m_info = info;
	m_level = level;

	auto ui = CSLoader::createNode("CardInfoLayer.csb");
	this->addChild(ui);

	m_closeBtn = (Button *)ui->getChildByName("btnClose");

	m_cardInfo = (Text*)ui->getChildByName("cardInfo");
	m_cardLevel = (Text*)ui->getChildByName("cardLevel");
	m_cardName = (Text*)ui->getChildByName("cardName");
	//触控监听
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CardInfoLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	listener->setSwallowTouches(true);
	m_closeBtn->addTouchEventListener(this, toucheventselector(CardInfoLayer::onCloseBtnClick));
	//显示卡片名称、等级、作用
	m_cardName->setText(CARD_NAME[m_info]);
	m_cardLevel->setText(StringUtils::format("%d", m_level));
	m_cardInfo->setText(TOLL_NAME[m_info] + "\n" + "Time " + " + " + StringUtils::format("%d", m_level * 200) + "ms");
	return true;
}

void CardInfoLayer::onCloseBtnClick(Ref* pSender, TouchEventType type)
{
	if(type == TOUCH_EVENT_ENDED)
	{
		this->removeFromParent();
	}
}

bool CardInfoLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	return true;
}
