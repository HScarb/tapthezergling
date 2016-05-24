// TollgateScene.cpp
#include "TollgateScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "GameManager.h"
#include "Global.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

cocos2d::Scene* TollgateScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TollgateScene::create();
	scene->addChild(layer);
	return scene;
}

bool TollgateScene::init()
{
	if (!Layer::init())
		return false;

	m_energyText = nullptr;
	m_jewelText = nullptr;
	m_addJewelBtn = nullptr;
	m_cardBtn = nullptr;
	m_homeBtn = nullptr;
	m_energyBar = nullptr;
	m_timeText = nullptr;
	m_timeBar = nullptr;

	m_scrollView = nullptr;
	m_t1 = nullptr;
	m_t2 = nullptr;
	m_t3 = nullptr;

	// 加载UI
	auto rootNode = CSLoader::createNode("TollgateScene.csb");
	addChild(rootNode);

	// 载入其他
	m_energyText = (Text*)(rootNode->getChildByName("Text_energy"));
	m_jewelText = (Text*)(rootNode->getChildByName("Text_jewel"));
	m_homeBtn = (Button*)(rootNode->getChildByName("Button_home"));
	m_cardBtn = (Button*)(rootNode->getChildByName("Button_cards"));
	// m_addJewelBtn = (Button*)(rootNode->getChildByName(""));
	m_energyBar = (LoadingBar*)(rootNode->getChildByName("LoadingBar_energy"));
	m_timeText = (Text*)rootNode->getChildByName("Text_time");
	m_timeBar = (LoadingBar*)rootNode->getChildByName("LoadingBar_time");

	m_scrollView = (ScrollView*)(rootNode->getChildByName("ScrollView"));
	m_t1 = (Text*)(m_scrollView->getChildByName("Text_1"));
	m_t2 = (Text*)(m_scrollView->getChildByName("Text_2"));
	m_t3 = (Text*)(m_scrollView->getChildByName("Text_3"));
	m_t4 = (Text*)(m_scrollView->getChildByName("Text_4"));
	m_t5 = (Text*)(m_scrollView->getChildByName("Text_5"));
	m_t6 = (Text*)(m_scrollView->getChildByName("Text_6"));
	m_t7 = (Text*)(m_scrollView->getChildByName("Text_7"));
	m_t8 = (Text*)(m_scrollView->getChildByName("Text_8"));

	m_energyText->setText("0");
	m_jewelText->setText("0");
	m_energyBar->setPercent(10.0f);
	m_timeBar->setPercent(100.0f);
	m_timeText->setText("00.00");
	
	// 设置时间
	if (GameManager::getInstance()->getIsGameOn() == false)		// 如果游戏还没有开始
	{
		TimeManager::getInstance()->setTime(INITIAL_TIME);
		GameManager::getInstance()->setIsGameOn(true);			// set game is on
	}
	else
	{
		TimeManager::getInstance()->addTime(2.0f);				// add 2 seconds
		CCLOG("added 2 seconds.");
	}

	m_timeText->setText(StringUtils::format("%05.2f", TimeManager::getInstance()->getTime()));		// 设置时间标签按照格式显示时间

	// 关联触摸函数
	// m_homeBtn->addTouchEventListener(CC_CALLBACK_1(TollgateScene::onHomeBtnClicked, this));
	m_homeBtn->addTouchEventListener(this, toucheventselector(TollgateScene::onHomeBtnClicked));
	m_t1->addTouchEventListener(this, toucheventselector(TollgateScene::onItem1Clicked));
	m_t2->addTouchEventListener(this, toucheventselector(TollgateScene::onItem2Clicked));
	m_t3->addTouchEventListener(this, toucheventselector(TollgateScene::onItem3Clicked));
	m_t4->addTouchEventListener(this, toucheventselector(TollgateScene::onItem4Clicked));
	m_t5->addTouchEventListener(this, toucheventselector(TollgateScene::onItem5Clicked));
	m_t6->addTouchEventListener(this, toucheventselector(TollgateScene::onItem6Clicked));
	m_t7->addTouchEventListener(this, toucheventselector(TollgateScene::onItem7Clicked));
	m_t8->addTouchEventListener(this, toucheventselector(TollgateScene::onItem8Clicked));
	return true;
}

void TollgateScene::onHomeBtnClicked(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::MainScene);
}

void TollgateScene::onCardBtnClicked(Ref* pSender, TouchEventType type)
{
	
}

void TollgateScene::onItem1Clicked(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED) 
	{
		log("tollgate 1");
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::DoubleTapScene, 0, 3);
	}
}

void TollgateScene::onItem2Clicked(Ref* pSender, TouchEventType type)
{
	if(type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		log("tollgate 2");
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::SlideCutScene, 0, 2);
	}
}

void TollgateScene::onItem3Clicked(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		log("tollgate 3");
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::EatCandiesScene, 0, 1);
	}
}
void TollgateScene::onItem4Clicked(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		log("tollgate 4");
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::BurrowAndAttackScene, 0, 2);
	}
}

void TollgateScene::onItem5Clicked(Ref* pSender, TouchEventType type)
{
	if(type == TOUCH_EVENT_ENDED)
	{
		log("tollgate 5");
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::JumpingOnPoolScene, 1, 2);
	}
}

void TollgateScene::onItem6Clicked(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		log("tollgate 6");
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::ClassifyUnits, 1, 2);
	}
}

void TollgateScene::onItem7Clicked(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if(type == TOUCH_EVENT_ENDED)
	{
		log("tollgate 7");
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::BOSS1);
	}
}

void TollgateScene::onItem8Clicked(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if(type == TOUCH_EVENT_ENDED)
	{
		log("tollgate 8");
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::BOSS2);
	}
}