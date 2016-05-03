// TollgateControlLayer.cpp
#include "TollgateControlLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "PauseLayer.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

Scene * TollgateControlLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = TollgateControlLayer::create();
	scene->addChild(layer);
	return scene;
}

bool TollgateControlLayer::init()
{
	if (!Layer::init())
		return false;

	auto UI = CSLoader::createNode("TollgateControlLayer.csb");
	addChild(UI);

	m_pauseBtn = (Button*)(UI->getChildByName("Button_pause"));
	m_timeBar = (LoadingBar*)(UI->getChildByName("LoadingBar_time"));
	m_timeText = (Text*)(UI->getChildByName("Text_time"));
	
	auto item1 = MenuItemLabel::create(Label::create("1111", "Arial", 36),
		CC_CALLBACK_1(TollgateControlLayer::menuItem1Callback, this));
	auto item2 = MenuItemLabel::create(Label::create("2222", "Arial", 36),
		CC_CALLBACK_1(TollgateControlLayer::menuItem2Callback, this));
	auto menu = Menu::create(item1, item2, nullptr);
	this->addChild(menu);

	m_pauseBtn->addTouchEventListener(this, toucheventselector(TollgateControlLayer::onPauseBtnClick));
	return true;
}

void TollgateControlLayer::menuItem1Callback(cocos2d::Ref* pSender)
{
	return;
}

void TollgateControlLayer::menuItem2Callback(cocos2d::Ref* pSender)
{
	return;
}

bool TollgateControlLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	return true;
}

void TollgateControlLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event) {}

void TollgateControlLayer::onPauseBtnClick(Ref*, cocos2d::ui::TouchEventType type)
{
	switch(type)
	{
	case TOUCH_EVENT_BEGAN: 
		log("tapped");
		break;
	case TOUCH_EVENT_MOVED: break;
	case TOUCH_EVENT_ENDED: break;
	case TOUCH_EVENT_CANCELED: break;
	default: break;
	}
}