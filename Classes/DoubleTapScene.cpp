// DoubleTapScene.cpp
#include "DoubleTapScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

const int GRID_WIDTH = 80;

Scene* DoubleTapScene::createScene(int diff, int loop)
{
	auto scene = Scene::create();
	auto layer = DoubleTapScene::create(diff, loop);
	scene->addChild(layer);
	return scene;
}

bool DoubleTapScene::init(int diff, int loop)
{
	if (!Layer::init())
		return false;
	
	auto UI = CSLoader::createNode("Doubletap.csb");
	addChild(UI);

	m_pauseBtn = (Button*)(UI->getChildByName("Button_pause"));
	m_timeBar = (LoadingBar*)(UI->getChildByName("LoadingBar_time"));
	m_timeText = (Text*)(UI->getChildByName("Text_time"));

	return true;
}

cocos2d::Layer* DoubleTapScene::create(int diff, int loop)
{
	auto pRef = new DoubleTapScene();
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
}

void DoubleTapScene::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* unused_event)
{
	int count = touches.size();
	if(count == 2)
	{
		for(auto &item: touches)
		{
			auto touch = item;
			auto location = touch->getLocation();

		}
	}
}

void DoubleTapScene::newLevel(int diff)
{
	
}