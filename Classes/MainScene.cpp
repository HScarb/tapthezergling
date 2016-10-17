// MainScene.cpp
#include "Chest.h"
#include "MainScene.h"
#include "AnimationUtil.h"
#include "cocostudio/CocoStudio.h"
#include "SceneManager.h"
#include "DataManager.h"
#include "SimpleAudioEngine.h"
#include "SoundManager.h"

USING_NS_CC;
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
	
	m_energyText = nullptr;
	m_jewelText = nullptr;
	m_scoreText = nullptr;
	m_addJewelBtn = nullptr;
	m_cardBtn = nullptr;
	m_settingsBtn = nullptr;
	m_energyBar = nullptr;

	m_zergling = nullptr;
	chest_sprite = nullptr;
	// 加载UI
	auto rootNode = CSLoader::createNode("MainScene.csb");
	addChild(rootNode);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* chest_sprite = Sprite::create("res/images/chest/chest_diamond_open1.png");
	chest_sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	chest_sprite->setScale(0.75, 0.75);
	this->addChild(chest_sprite);

	chest_sprite->setVisible(true);
	//chest_sprite->runAction(createAnimate());
	// 添加狗的动画
	/*
	auto visibleSize = Director::getInstance()->getVisibleSize();
	m_zergling = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("zergling_big_1.png"));
	m_zergling->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 20);
	m_zergling->setScale(0.3, 0.3);
	this->addChild(m_zergling);
	Animation * animation = AnimationUtil::createWithFrameNameAndNum("zergling_big_", 4, 0.08f, -1, true);
	m_zergling->runAction(Animate::create(animation));
	*/

	//添加宝箱
	/*
	auto visibleSize = Director::getInstance()->getVisibleSize();
	m_chest = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("chest_diamond_open1.png"));
	m_chest->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(m_chest);
	Animation * animation = AnimationUtil::createWithFrameNameAndNum("chest_diamond_open", 2, 0.08f, -1, true);
	m_chest->runAction(Animate::create(animation));
	*/

	// 载入其他
	m_energyText = (Text*)(rootNode->getChildByName("Text_energy"));
	m_jewelText = (Text*)(rootNode->getChildByName("Text_jewel"));
	m_scoreText = (Text*)(rootNode->getChildByName("Text_best_score"));
	m_settingsBtn = (Button*)(rootNode->getChildByName("Button_settings"));
	m_cardBtn = (Button*)(rootNode->getChildByName("Button_cards"));
	// m_addJewelBtn = (Button*)(rootNode->getChildByName(""));
	m_energyBar = (LoadingBar*)(rootNode->getChildByName("LoadingBar_energy"));

	DataManager::getInstance()->loadData();

	m_energyText->setText("0");
	m_jewelText->setText("0");
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
	if (chest_sprite->getBoundingBox().containsPoint(pos))
	{
		//chest_sprite->runAction(createAnimate());
		chest_sprite->setVisible(false);
	}
}


void MainScene::onSettingsBtnClick(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		SceneManager::getInstance()->changeScene(SceneManager::SettingsScene);
	}

}

void MainScene::onCardBtnClick(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
		return;
}

/*
cocos2d::Animate* MainScene::createAnimate()
{
	int iFrameNum = 2;
	SpriteFrame* frame = nullptr;
	Vector<SpriteFrame*> frameVec;
	

	for (int i = 1; i <= iFrameNum; i++)
	{
		frame = animation->getSpriteFrameByName(StringUtils::format("res/images/chest/chest_diamond_open%d.png", i));
		//frame = SpriteFrame::create(StringUtils::format("res/images/chest/chest_diamond_open%d", i), Rect(0, 0, 130, 130));
		frameVec.pushBack(frame);
	}
	
	return action;
}
*/

void MainScene::onAddJewelBtnClick(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
		return;
}