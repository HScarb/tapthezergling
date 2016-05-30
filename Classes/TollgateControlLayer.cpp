// TollgateControlLayer.cpp
#include "TollgateControlLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "PauseLayer.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "GameManager.h"
using namespace std;
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
	
	// ��Ӵ����ص�
	m_pauseBtn->addTouchEventListener(this, toucheventselector(TollgateControlLayer::onPauseBtnClick));
	
	// add custom event listener
	auto clearListener = EventListenerCustom::create("tollgate_clear", CC_CALLBACK_1(TollgateControlLayer::tollgateClear, this));
	auto failListener = EventListenerCustom::create("tollgate_fail", CC_CALLBACK_1(TollgateControlLayer::tollgateFail, this));

	_eventDispatcher->addEventListenerWithSceneGraphPriority(clearListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(failListener, this);

	return true;
}

void TollgateControlLayer::update(float dt)
{
	if(TimeManager::getInstance()->isCountingDown())
	{
		TimeManager::getInstance()->update(dt);
//		CCLOG("time = %f, pretime = %f", TimeManager::getInstance()->getTime(), TimeManager::getInstance()->getPreTime());
		m_timeBar->setPercent(TimeManager::getInstance()->getTime() / TimeManager::getInstance()->getPreTime() * 100.0f);		// ����ʱ�����������
		m_timeText->setText(StringUtils::format("%05.2f", TimeManager::getInstance()->getTime()));
	}
}

void TollgateControlLayer::tollgateClear(cocos2d::EventCustom * event)
{
	string * tollgate = (string*)event->getUserData();
	CCLOG("%s cleared.", tollgate);

	TimeManager::getInstance()->pauseCountDown();
	this->unscheduleUpdate();		// stop update for tollgate control layer
	GameManager::getInstance()->setIsWaitToAddTime(true);
	SceneManager::getInstance()->changeScene(SceneManager::SceneType::TollgateScene);
}

void TollgateControlLayer::tollgateFail(cocos2d::EventCustom * event)
{
	string * tollgate = (string*)event->getUserData();
	CCLOG("%s failed.\nGAME OVER", tollgate);
	// change to main scene
	TimeManager::getInstance()->pauseCountDown();
	GameManager::getInstance()->setIsGameOn(false);
	SceneManager::getInstance()->changeScene(SceneManager::SceneType::MainScene);
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