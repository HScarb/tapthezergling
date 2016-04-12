// SceneManager.cpp
#include "SceneManager.h"
#include "LoadingScene.h"
#include "MainScene.h"
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
	switch(sceneType)
	{
	case SceneManager::MainScene:
		pScene = MainScene::createScene();
		break;
	case SceneManager::LoadingScene:
		pScene = LoadingScene::createScene();
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