// SettingsScene.cpp
#include "SettingsScene.h"
#include "cocostudio/CocoStudio.h"
#include "SceneManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace CocosDenshion;

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

	Button* music = (Button*)Helper::seekWidgetByName(m_musicBtn, "music");
	//m_musictext = (*)
	//m_musicText = (*)Helper::seekWidg
	if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		/*
		LabelTTF *label1 = LabelTTF::create("MUSIC ON", "fonts/AveriaSansLibre-BoldItalic.ttf", 40);
		label1->setPosition(480, 351);
		label1->enableShadow(Size(1.50, -1.50), 2, 2);
		addChild(label1);
		*/
		m_musicBtn->setTitleFontSize(84);
		m_musicBtn->setTitleText("MUSIC ON");
	}

	if (!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		
		/*
		LabelTTF *label1 = LabelTTF::create("MUSIC OFF", "fonts/AveriaSansLibre-BoldItalic.ttf", 40);
		label1->setPosition(480, 351);
		label1->enableShadow(Size(1.50, -1.50), 2, 2);
		addChild(label1);
		*/
		m_musicBtn->setTitleFontSize(84);
		m_musicBtn->setTitleText("MUSIC OFF");
	}

//	m_homeBtn->addTouchEventListener(CC_CALLBACK_1(SettingsScene::onHomeBtnClick, this));
	m_homeBtn->addTouchEventListener(this, toucheventselector(SettingsScene::onHomeBtnClick));
	m_musicBtn->addTouchEventListener(this, toucheventselector(SettingsScene::onMusciBtnClick));

	return true;
}

void SettingsScene::onHomeBtnClick(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::MainScene);
}

void SettingsScene::onSoundBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{

}

void SettingsScene::onRestoreBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{

}

void SettingsScene::onAboutBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{

}

void SettingsScene::onMusciBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	/*
	if (type == TOUCH_EVENT_ENDED)
	{
		if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	else
	{
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
	*/
	if (type == TOUCH_EVENT_BEGAN)
	if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		//SimpleAudioEngine::sharedEngine()->pauseAllEffects();
		//此处修改off
		m_musicBtn->setTitleFontSize(84);
		//m_musicBtn->setTitleColor(Color3B::WHITE);默认是白色
		m_musicBtn->setTitleText("MUSIC OFF");
		/*
		LabelTTF *label1 = LabelTTF::create("MUSIC ON", "fonts/AveriaSansLibre-BoldItalic.ttf", 40);
		label1->setPosition(480, 351);
		label1->enableShadow(Size(1.50, -1.50), 2, 2);
		addChild(label1);
		*/
	}

	else
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		//此处修改on
		m_musicBtn->setTitleFontSize(84);
		//m_musicBtn->setTitleColor(Color3B::WHITE);
		m_musicBtn->setTitleText("MUSIC ON");
		/*
		LabelTTF *label2 = LabelTTF::create("MUSIC OFF", "fonts/AveriaSansLibre-BoldItalic.ttf", 40);
		label2->setPosition(480, 351);
		label2->enableShadow(Size(1.50, -1.50), 2, 2);
		addChild(label2);
		*/
	}

}