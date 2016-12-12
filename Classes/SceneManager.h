// SceneManager.h
#pragma once
#include "cocos2d.h"

class SceneManager : public cocos2d::Ref
{
public:
	typedef enum 
	{
		LoadingScene,
		MainScene,
		SettingsScene,
		TollgateScene,
		ScoreScene,
		BOSS1 = 101,
		BOSS2,
		BOSS3,
		BOSS4,
		BOSS5
	}SceneType;
	typedef enum
	{
		None,
		DoubleTapScene,
		SlideCutScene,
		EatCandiesScene,
		BurrowAndAttackScene,
		JumpingOnPoolScene,
		ClassifyUnits,
		CheckThethingScene,
		FeedSnacks,
		fitthecircle
	}TollgateSceneType;
	static SceneManager * getInstance();
	virtual bool init();

	void changeScene(SceneType sceneType);
	void changeScene(TollgateSceneType sceneType, int diff, int loop);

private:
	static SceneManager * m_sceneManager;
};