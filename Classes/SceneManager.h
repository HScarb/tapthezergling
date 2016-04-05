// SceneManager.h
#pragma once
#include "cocos2d.h"

class SceneManager : public cocos2d::Ref
{
public:
	enum SceneType
	{
		LoadingScene,
		MainScene,
		SettingsScene,
		TollgateScene
	};
	static SceneManager * getInstance();
	virtual bool init();

	void changeScene(SceneType sceneType);

private:
	static SceneManager * m_sceneManager;
};