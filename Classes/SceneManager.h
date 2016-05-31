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
		TollgateScene,
		BOSS1,
		BOSS2,
		BOSS3,
		BOSS4,
		BOSS5
	};
	enum TollgateSceneType
	{
		DoubleTapScene,
		SlideCutScene,
		EatCandiesScene,
		BurrowAndAttackScene,
		JumpingOnPoolScene,
		ClassifyUnits,
		CheckThethingScene
	};
	static SceneManager * getInstance();
	virtual bool init();

	void changeScene(SceneType sceneType);
	void changeScene(TollgateSceneType sceneType, int diff, int loop);

private:
	static SceneManager * m_sceneManager;
};