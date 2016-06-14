// ScoreScene.cpp
#include "ScoreScene.h"

#include "cocostudio/CocoStudio.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "DataManager.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

cocos2d::Scene* ScoreScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ScoreScene::create();
	scene->addChild(layer);
	return scene;
}

bool ScoreScene::init()
{
	if (!Layer::init())
		return false;
	m_homeBtn = nullptr;
	m_restartBtn = nullptr;
	m_scoreText = nullptr;

	auto ui = CSLoader::createNode("ScoreScene.csb");
	this->addChild(ui);

	// 从ui中加载按钮
	m_homeBtn = (Button*)ui->getChildByName("Button_home");
	m_restartBtn = (Button*)ui->getChildByName("Button_restart");
	m_scoreText = (Text*)ui->getChildByName("Text_score");

	m_scoreText->setText(StringUtils::format("%d", GameManager::getInstance()->getScore()));
	m_scoreText->setScale(0.0);
	m_scoreText->runAction(ScaleTo::create(0.2, 1.0));

	if (DataManager::getInstance()->getBestScore() < GameManager::getInstance()->getScore())
	{
		auto dm = DataManager::getInstance();
		int s = GameManager::getInstance()->getScore();
		if (s > dm->getBestScore())
			dm->setBestScore(s);
		DataManager::getInstance()->saveData();
	}
	GameManager::getInstance()->resetTollgateData();
	
	//	m_homeBtn->addTouchEventListener(CC_CALLBACK_1(SettingsScene::onHomeBtnClick, this));
	m_homeBtn->addTouchEventListener(this, toucheventselector(ScoreScene::onHomeBtnClick));
	m_restartBtn->addTouchEventListener(this, toucheventselector(ScoreScene::onRestartBtnClick));
	return true;
}

void ScoreScene::onHomeBtnClick(Ref* pSender, TouchEventType type)
{
	if(type == TOUCH_EVENT_ENDED)
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::MainScene);
}

void ScoreScene::onRestartBtnClick(Ref* pSender, TouchEventType type)
{
	if(type == TOUCH_EVENT_ENDED)
		SceneManager::getInstance()->changeScene(SceneManager::TollgateScene);
}