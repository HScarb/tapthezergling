// TollgateScene.cpp
#include "TollgateScene.h"
USING_NS_CC;

cocos2d::Scene* TollgateScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TollgateScene::create();
	scene->addChild(layer);
	return scene;
}

bool TollgateScene::init()
{
	if (!Layer::init())
		return false;

	return true;
}