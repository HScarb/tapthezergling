// PauseLayer.cpp
#include "PauseLayer.h"
USING_NS_CC;

bool PauseLayer::init()
{
	if (!Layer::init())
		return false;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(PauseLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PauseLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PauseLayer::onTouchEnded, this);
	return true;
}

bool PauseLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	return true;
}

void PauseLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event) {}

void PauseLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event) {}