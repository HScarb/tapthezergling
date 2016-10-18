// PauseLayer.cpp
#include "PauseLayer.h"
#include "cocostudio/CocoStudio.h"
#include "TimeManager.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

bool PauseLayer::init()
{
	if (!Layer::init())
		return false;

	auto UI = CSLoader::createNode("PauseLayer.csb");
	addChild(UI);
	m_resumeBtn = (Button*)(UI->getChildByName("Button_resume"));

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(PauseLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PauseLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PauseLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	listener->setSwallowTouches(true);		// �����̲��ϲ㴥��

	m_resumeBtn->addTouchEventListener(this, toucheventselector(PauseLayer::onResumeBtnClick));
	return true;
}

bool PauseLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	return true;
}

void PauseLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event) {}

void PauseLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event) {}

void PauseLayer::onResumeBtnClick(Ref*, cocos2d::ui::TouchEventType type)
{
	if(type == TOUCH_EVENT_ENDED)
	{
		TimeManager::getInstance()->resumeCountDown();
		this->removeFromParent();
	}
}