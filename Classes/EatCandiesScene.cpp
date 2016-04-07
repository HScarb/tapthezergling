//EacCandiesScnen.cpp
#include "EatCandiesScene.h"
USING_NS_CC;

Scene* EatCandiesScene::createScene(int diff, int loop)
{
	auto scene = Scene::create();
	auto layer = EatCandiesScene::create(diff,loop);
	scene->addChild(layer);
	return scene;
}

bool EatCandiesScene::init(int diff, int loop)
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}

cocos2d::Layer* EatCandiesScene::create(int diff, int loop)
{
	auto pRef = new EatCandiesScene();
	if (pRef && pRef->init(diff, loop))
	{
		pRef->autorelease();
		return pRef;
	}
	else
	{
		CC_SAFE_DELETE(pRef);
		return nullptr;
}


	



