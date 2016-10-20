// NoTouchLayer.cpp
#include "NoTouchLayer.h"

USING_NS_CC;

Scene* NoTouchLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = NoTouchLayer::create();
	scene->addChild(scene);
	return scene;
}

bool NoTouchLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(NoTouchLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(NoTouchLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(NoTouchLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	listener->setSwallowTouches(true);
	return true;
}

bool NoTouchLayer::onTouchBegan(Touch* touch, Event* unused_event)
{
	log("notouchlayerbegin");
	return true;
}

void NoTouchLayer::onTouchMoved(Touch* touch, Event* unused_event)
{
}

void NoTouchLayer::onTouchEnded(Touch* touch, Event* unused_event)
{
}
