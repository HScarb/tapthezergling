// MainScene.cpp
#include "MainScene.h"
#include "AnimationUtil.h"
#include "cocostudio/CocoStudio.h"
#include "SceneManager.h"
#include "DataManager.h"
#include "SimpleAudioEngine.h"
#include "SoundManager.h"
#include "CardControlLayer.h"
#include "NoTouchLayer.h"
#include "GameManager.h"
#include "StringUtil.h"
#include "CsvUtil.h"

USING_NS_CC;

int new1 = 1;			//初始打开的情况下，给与30点能量值

using namespace CocosDenshion;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

cocos2d::Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainScene::init()
{
	if (!Layer::init())
		return false;

	///////////////////////////////////////////////////////
	/*以下是测试Csv部分*/
	auto strsList = StringUtil::getInstance()->split("Muton,xiaoruo,cocos2d-x,Csv", ",");

	for (auto value : strsList)
	{
		log("value = %s", value.asString().c_str());
	}

	const char * sPath = "Cards.csv";
	CsvUtil::getInstance()->loadFile(sPath);

	Value CardLevel = CsvUtil::getInstance()->getValue(2, 1, sPath);

	Value CardPosition = CsvUtil::getInstance()->getValue(2, 2, sPath);

	log("CardLevel = %s", CardLevel.asString().c_str());
	log("CardPosition = %s", CardPosition.asString().c_str());

	UserDefault::sharedUserDefault()->setStringForKey("CardName", "EatFlowers");

	String * CardName = String::create(UserDefault::sharedUserDefault()->getStringForKey("CardName"));

	log("CardName = %s", CardName->getCString());

	//////////////////////////////////////////////////////
	m_energyText = nullptr;
	m_jewelText = nullptr;
	m_scoreText = nullptr;
	m_addJewelBtn = nullptr;
	m_cardBtn = nullptr;
	m_settingsBtn = nullptr;
	m_energyBar = nullptr;

	m_zergling = nullptr;

	//30点能量
	if (new1 == 1)
	{
		GameManager::getInstance()->setEnergy(30);
		new1 = -1;
	}
	else {}
	
	//自然回复能量
	if (GameManager::getInstance()->getEnergy() < 30)
	{
		this->schedule(schedule_selector(MainScene::resumeEnergy), 60.0f);
		log("%d", GameManager::getInstance()->getEnergy());
	}

	// 加载UI
	auto rootNode = CSLoader::createNode("MainScene.csb");
	addChild(rootNode);

	//加载卡片合成层
	/*m_cardControlLayer = CardControlLayer::create();
	this->addChild(m_cardControlLayer, 11);
	m_cardControlLayer->setVisible(false);*/
	
	// 添加狗的动画
	auto visibleSize = Director::getInstance()->getVisibleSize();
	m_zergling = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("zergling_big_1.png"));
	m_zergling->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 20);
	m_zergling->setScale(0.3, 0.3);
	this->addChild(m_zergling);
	Animation * animation = AnimationUtil::createWithFrameNameAndNum("zergling_big_", 4, 0.08f, -1, true);
	m_zergling->runAction(Animate::create(animation));

	// 载入其他
	m_energyText = (Text*)(rootNode->getChildByName("Text_energy"));
	m_jewelText = (Text*)(rootNode->getChildByName("Text_jewel"));
	m_scoreText = (Text*)(rootNode->getChildByName("Text_best_score"));
	m_settingsBtn = (Button*)(rootNode->getChildByName("Button_settings"));
	m_cardBtn = (Button*)(rootNode->getChildByName("Button_cards"));
	// m_addJewelBtn = (Button*)(rootNode->getChildByName(""));
	m_energyBar = (LoadingBar*)(rootNode->getChildByName("LoadingBar_energy"));

	DataManager::getInstance()->loadData();

	m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
	m_jewelText->setText(StringUtils::format("%d", GameManager::getInstance()->getJewel()));
	m_scoreText->setText(StringUtils::format("%d", DataManager::getInstance()->getBestScore()));
	m_energyBar->setPercent(10.0f);

	// 为按钮添加点击事件
	m_settingsBtn->addTouchEventListener(this, toucheventselector(MainScene::onSettingsBtnClick));
	m_cardBtn->addTouchEventListener(this, toucheventselector(MainScene::onCardBtnClick));
	//	m_addJewelBtn->addTouchEventListener(this, toucheventselector(MainScene::onAddJewelBtnClick));
	//	m_settingsBtn->addTouchEventListener(CC_CALLBACK_1(MainScene::onSettingsBtnClick, this));
	//	m_cardBtn->addTouchEventListener(CC_CALLBACK_1(MainScene::onCardBtnClick, this));
	// m_addJewelBtn->addTouchEventListener(CC_CALLBACK_1(MainScene::onAddJewelBtnClick, this));


	// 添加触摸监听
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	SoundManager::getInstance()->playMenuMusic();

	return true;
}

bool MainScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	return true;
}

void MainScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	auto pos = touch->getLocation();
	if (m_zergling->getBoundingBox().containsPoint(pos))
	{
		SceneManager::getInstance()->changeScene(SceneManager::TollgateScene);
	}
}

void MainScene::onSettingsBtnClick(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
		SceneManager::getInstance()->changeScene(SceneManager::SettingsScene);
}

void MainScene::onCardBtnClick(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		//m_cardControlLayer->showLayer();
		m_cardControlLayer = CardControlLayer::create();
		this->addChild(m_cardControlLayer);
	}
	return;
}

void MainScene::resumeEnergy(float dt)
{
	if (GameManager::getInstance()->getEnergy() < 30){
		GameManager::getInstance()->setEnergy(GameManager::getInstance()->getEnergy() + 1);
		m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
	}
}

void MainScene::onAddJewelBtnClick(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
		return;
}