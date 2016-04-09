//EacCandiesScnen.cpp
#include "EatCandiesScene.h"
#include "cocos2d.h"
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

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event)
	{
		Point pos1 = touch->getLocation();
		Point pos2 = touch->getLocationInView();
		Point pos3 = Director::getInstance()->convertToGL(pos2);
		return true;
	};

	listener->onTouchMoved = [](Touch* touch, Event* event){};
	
	listener->onTouchEnded = [=](Touch* touch, Event* event){};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

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


	



