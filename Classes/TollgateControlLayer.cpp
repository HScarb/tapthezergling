// TollgateControlLayer.cpp
#include "TollgateControlLayer.h"
#include "cocostudio/CocoStudio.h"
#include "PauseLayer.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "GlobalConst.h"
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
	
	// 添加触摸回调
	m_pauseBtn->addTouchEventListener(this, toucheventselector(TollgateControlLayer::onPauseBtnClick));
	
	// add custom event listener
	auto clearListener = EventListenerCustom::create("tollgate_clear", CC_CALLBACK_1(TollgateControlLayer::tollgateClear, this));
	auto failListener = EventListenerCustom::create("tollgate_fail", CC_CALLBACK_1(TollgateControlLayer::tollgateFail, this));

	_eventDispatcher->addEventListenerWithSceneGraphPriority(clearListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(failListener, this);

	// 播放背景音乐
	SoundManager::getInstance()->playTollgateMusic();

	return true;
}

void TollgateControlLayer::update(float dt)
{
	if(TimeManager::getInstance()->isCountingDown())
	{
		TimeManager::getInstance()->update(dt);
//		CCLOG("time = %f, pretime = %f", TimeManager::getInstance()->getTime(), TimeManager::getInstance()->getPreTime());
		m_timeBar->setPercent(TimeManager::getInstance()->getTime() / TimeManager::getInstance()->getPreTime() * 100.0f);		// 设置时间进度条进度
		m_timeText->setText(StringUtils::format("%05.2f", TimeManager::getInstance()->getTime()));
	}
}

/* 过关函数 */
void TollgateControlLayer::tollgateClear(cocos2d::EventCustom * event)
{
	string * tollgate = (string*)event->getUserData();
	CCLOG("%s cleared.", tollgate);

	TimeManager::getInstance()->pauseCountDown();
	TimeManager::getInstance()->setisTollgateBegin(false);		// 设置关卡没有开始
	this->unscheduleUpdate();		// stop update for tollgate control layer
	GameManager::getInstance()->setIsWaitToAddTime(true);
	// 判断是否出现宝箱
	if (/*GameManager::getInstance()->getTollgateNum() % 10 == CHEST_TOLLGATE && GameManager::getInstance()->getTollgateNum()!= 1)*/
		GameManager::getInstance()->getTollgateNum() % CHEST_TOLLGATE == 0)
	{
		GameManager::getInstance()->setIsWaitToAddChest(true);
	}
	// 播放菜单背景音乐
	SoundManager::getInstance()->forcePlayMenuMusic();
	SceneManager::getInstance()->changeScene(SceneManager::SceneType::TollgateScene);
}

void TollgateControlLayer::tollgateFail(cocos2d::EventCustom * event)
{
	string * tollgate = (string*)event->getUserData();
	CCLOG("%s failed.\nGAME OVER", tollgate);
	// change to main scene
	TimeManager::getInstance()->pauseCountDown();
	TimeManager::getInstance()->setisTollgateBegin(false);		// 设置关卡没有开始
	// 停止背景音乐并且播放胜利音效
	SoundManager::getInstance()->stopMusic();
	SoundManager::getInstance()->playEffect("Sounds/winmusic.mp3");
	SceneManager::getInstance()->changeScene(SceneManager::SceneType::ScoreScene);
}

void TollgateControlLayer::initTimeBar()
{
	m_timeText->setText(StringUtils::format("%05.2f", TimeManager::getInstance()->getTime()));
	return;
}

// 当暂停按钮被点击
void TollgateControlLayer::onPauseBtnClick(Ref*, cocos2d::ui::TouchEventType type)
{
	if(type == TOUCH_EVENT_ENDED)
	{
		CCLOG("Pause button clicked");
		auto pauseLayer = PauseLayer::create();
		this->addChild(pauseLayer);
		TimeManager::getInstance()->pauseCountDown();
	}
	
}