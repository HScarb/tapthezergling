// MainScene.cpp
#include "MainScene.h"
#include "AnimationUtil.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
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

	// 加载UI
	auto rootNode = CSLoader::createNode("MainScene.csb");
	addChild(rootNode);

	// 添加狗的动画
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto dog = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("zergling_big_1.png"));
	dog->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 20);
	dog->setScale(0.3, 0.3);
	this->addChild(dog);
	Animation * animation = AnimationUtil::createWithFrameNameAndNum("zergling_big_", 4, 0.08f, -1, true);
	dog->runAction(Animate::create(animation));

	// 载入其他
	m_energyText = (Text*)(rootNode->getChildByName("Text_energy"));
	m_jewelText = (Text*)(rootNode->getChildByName("Text_jewel"));
	m_scoreText = (Text*)(rootNode->getChildByName("Text_best_score"));
	m_settingsBtn = (Button*)(rootNode->getChildByName("Button_settings"));
	m_cardBtn = (Button*)(rootNode->getChildByName("Button_cards"));
	// m_addJewelBtn = (Button*)(rootNode->getChildByName(""));
	m_energyBar = (LoadingBar*)(rootNode->getChildByName("LoadingBar_energy"));

	m_energyText->setText("0");
	m_jewelText->setText("0");
	m_scoreText->setText("0");
	m_energyBar->setPercent(10.0f);

	return true;
}