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
	enum TollgateSceneType
	{
		DoubleTapScene,
		SlideCutScene,
		EatCandiesScene,
		BurrowAndAttackScene,
		JumpingOnPoolScene,
	};
	static SceneManager * getInstance();
	virtual bool init();

	void changeScene(SceneType sceneType);
	void changeScene(TollgateSceneType sceneType, int diff, int loop);

private:
	static SceneManager * m_sceneManager;
};