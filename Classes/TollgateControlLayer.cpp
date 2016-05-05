// TollgateControlLayer.cpp
#include "TollgateControlLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "PauseLayer.h"
#include "TimeManager.h"
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

	m_timeBar->setPercent(100.0f);
	m_timeText->setText("00.00");
	
	// 添加触摸回调
	m_pauseBtn->addTouchEventListener(this, toucheventselector(TollgateControlLayer::onPauseBtnClick));
	return true;
}

void TollgateControlLayer::update(float dt)
{
	if(TimeManager::getInstance()->isCountingDown())
	{
		TimeManager::getInstance()->update(dt);
		CCLOG("time = %f, pretime = %f", TimeManager::getInstance()->getTime(), TimeManager::getInstance()->getPreTime());
		m_timeBar->setPercent(TimeManager::getInstance()->getTime() / TimeManager::getInstance()->getPreTime() * 100.0f);		// 设置时间进度条进度
		m_timeText->setText(StringUtils::format("%05.2f", TimeManager::getInstance()->getTime()));
	}
}

void TollgateControlLayer::initTimeBar()
{
	m_timeText->setText(StringUtils::format("%05.2f", TimeManager::getInstance()->getTime()));
	return;
}

void TollgateControlLayer::onPauseBtnClick(Ref*, cocos2d::ui::TouchEventType type)
{
	switch(type)
	{
	case TOUCH_EVENT_BEGAN: break;
	case TOUCH_EVENT_MOVED: break;
	case TOUCH_EVENT_ENDED: 
		CCLOG("Pause btn tapped");
		break;
	case TOUCH_EVENT_CANCELED: break;
	default: break;
	}
}