// SettingsScene.cpp
#include "SettingsScene.h"
#include "cocostudio/CocoStudio.h"
#include "SceneManager.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

cocos2d::Scene* SettingsScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SettingsScene::create();
	scene->addChild(layer);
	return scene;
}

bool SettingsScene::init()
{
	if (!Layer::init())
		return false;
	m_homeBtn = nullptr;
	m_soundBtn = nullptr;
	m_musicBtn = nullptr;
	m_restoreBtn = nullptr;
	m_aboutBtn = nullptr;

	auto ui = CSLoader::createNode("SettingsScene.csb");
	this->addChild(ui);

	// 从ui中加载按钮
	m_homeBtn = (Button*)ui->getChildByName("Button_home");
	m_soundBtn = (Button*)ui->getChildByName("Button_sound");
	m_musicBtn = (Button*)ui->getChildByName("Button_music");
	m_restoreBtn = (Button*)ui->getChildByName("Button_restore");
	m_aboutBtn = (Button*)ui->getChildByName("Button_about");

//	m_homeBtn->addTouchEventListener(CC_CALLBACK_1(SettingsScene::onHomeBtnClick, this));
	m_homeBtn->addTouchEventListener(this, toucheventselector(SettingsScene::onHomeBtnClick));
	return true;
}

void SettingsScene::onHomeBtnClick(Ref* pSender, TouchEventType type)
{
	SceneManager::getInstance()->changeScene(SceneManager::SceneType::MainScene);
}