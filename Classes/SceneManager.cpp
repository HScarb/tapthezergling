// SceneManager.cpp
#include "SceneManager.h"
#include "LoadingScene.h"
#include "MainScene.h"
#include "TollgateControlLayer.h"
#include "TollgateScene.h"
#include "SettingsScene.h"
#include "ScoreScene.h"

#include "DoubleTapScene.h"
#include "SlideCutScene.h"
#include "EatCandiesScene.h"
#include "BurrowAndAttack.h"
#include "JumpingOnPoolScene.h"
#include "ClassifyUnits.h"
#include "BOSS1ZerglingKing.h"
#include "BOSS2ZerglingNinja.h"
#include "CheckThethingScene.h"
#include"FeedSnacks.h"
#include "fitthecircle.h"
USING_NS_CC;

SceneManager * SceneManager::m_sceneManager = nullptr;

SceneManager* SceneManager::getInstance()
{
	if(m_sceneManager == nullptr)
	{
		m_sceneManager = new SceneManager();
		if(m_sceneManager && m_sceneManager->init())
		{
			m_sceneManager->autorelease();
			m_sceneManager->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_sceneManager);
			m_sceneManager = nullptr;
		}
	}
	return m_sceneManager;
}

bool SceneManager::init()
{
	return true;
}

void SceneManager::changeScene(SceneType sceneType)
{
	Scene * pScene = nullptr;
	Layer * pLayer = nullptr;
	switch(sceneType)
	{
	case SceneManager::MainScene:
		pScene = MainScene::createScene();
		break;
	case SceneManager::LoadingScene:
		pScene = LoadingScene::createScene();
		break;
	case SceneManager::TollgateScene:
		pScene = TollgateScene::createScene();
		break;
	case SceneManager::SettingsScene:
		pScene = SettingsScene::createScene();
		break;
	case SceneManager::ScoreScene:
		pScene = ScoreScene::createScene();
		break;
		break;
	case SceneManager::BOSS1:
		pScene = BOSS1ZerglingKing::createScene();
		break;
	case SceneManager::BOSS2:
		pScene = BOSS2ZerglingNinja::createScene();
		break;
	case SceneManager::BOSS3:
		break;
	case SceneManager::BOSS4:
		break;
	case SceneManager::BOSS5:
		break;
	default:
		break;
	}

	Director * pDirector = Director::getInstance();
	Scene * curScene = pDirector->getRunningScene();
	if (curScene == nullptr)
	{
		pDirector->runWithScene(pScene);
	}
	else
	{
		auto replaceScene = TransitionFade::create(0.8f, pScene);
		pDirector->replaceScene(replaceScene);
	}
}

void SceneManager::changeScene(TollgateSceneType sceneType, int diff, int loop)
{
	Scene * pScene = nullptr;
	switch (sceneType)
	{
	case DoubleTapScene: 
		pScene = DoubleTapScene::createScene(diff, loop);
		break;
	case SlideCutScene: 
		pScene = SlideCutScene::createScene(diff, loop);
		break;
	case EatCandiesScene:
		pScene = EatCandiesScene::createScene(diff,loop);
		break;
	case BurrowAndAttackScene:
		pScene = BurrowAndAttackScene::createScene(diff, loop);
		break;
	case JumpingOnPoolScene:
		pScene = JumpingOnPoolScene::createScene(diff, loop);
		break;
	case ClassifyUnits:
		pScene = ClassifyUnits::createScene(diff, loop);
		break;
	case CheckThethingScene:
		pScene = CheckThethingScene::createScene(diff, loop);
		break;
	case FeedSnacks:
		pScene = FeedSnacks::createScene(diff, loop);
		break;
	case fitthecircle:
		pScene = fitthecircleScene::createScene(diff, loop);
		break;
	default: break;
	}
	auto pDirector = Director::getInstance();
	auto curScene = pDirector->getRunningScene();
	if (curScene == nullptr)
	{
		pDirector->runWithScene(pScene);
	}
	else
	{
		auto replaceScene = TransitionFade::create(0.8f, pScene);
		pDirector->replaceScene(replaceScene);
	}
}

