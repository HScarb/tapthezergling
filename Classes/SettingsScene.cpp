// SettingsScene.cpp
#include "SettingsScene.h"
#include "cocostudio/CocoStudio.h"
#include "SceneManager.h"
#include "SimpleAudioEngine.h"
#include "SoundManager.h"

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
	m_soundText = nullptr;
	m_musicText = nullptr;

	auto ui = CSLoader::createNode("SettingsScene.csb");
	this->addChild(ui);

	// ��ui�м��ذ�ť
	m_homeBtn = (Button*)ui->getChildByName("Button_home");
	m_soundBtn = (Button*)ui->getChildByName("Button_sound");
	m_musicBtn = (Button*)ui->getChildByName("Button_music");
	m_restoreBtn = (Button*)ui->getChildByName("Button_restore");
	m_aboutBtn = (Button*)ui->getChildByName("Button_about");
	// ��ui�м��ذ�ť�ı�
	m_soundText = (Text*)ui->getChildByName("Text_sound");
	m_musicText = (Text*)ui->getChildByName("Text_music");

	// �󶨰�ť���µĻص�����
	m_homeBtn->addTouchEventListener(this, toucheventselector(SettingsScene::onHomeBtnClick));
	m_soundBtn->addTouchEventListener(this, toucheventselector(SettingsScene::onSoundBtnClick));
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
	if (type == TOUCH_EVENT_ENDED)
	{
		// �����Ч�������ڵ�ֵ�����ҷ�ת
		if(SoundManager::getInstance()->getSoundOn())
		{
			m_soundText->setText("SOUND OFF");		// �����ı�
			SoundManager::getInstance()->setSoundOn(false);
		}
		else
		{
			m_soundText->setText("SOUND ON");
			SoundManager::getInstance()->setSoundOn(true);
		}
	}
}

void SettingsScene::onMusciBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		// ������ֿ������ڵ�ֵ�����ҷ�ת
		if (SoundManager::getInstance()->getMusicOn())
		{
			m_musicText->setText("MUSIC OFF");		// ����Ϊ��Ϊ��
			SoundManager::getInstance()->setMusicOn(false);
			SoundManager::getInstance()->stopMusic();
		}
		else
		{
			m_musicText->setText("MUSIC ON");
			SoundManager::getInstance()->setMusicOn(true);
			SoundManager::getInstance()->playMenuMusic();
		}
	}
}

void SettingsScene::onRestoreBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{

}

void SettingsScene::onAboutBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{

}