// BOSS2ZerglingNinja
#include "BOSS2ZerglingNinja.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
using namespace std;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
USING_NS_CC;

cocos2d::Scene* BOSS2ZerglingNinja::createScene()
{
	auto scene = Scene::create();
	auto layer = BOSS2ZerglingNinja::create();
	scene->addChild(layer);
	return scene;
}

bool BOSS2ZerglingNinja::init()
{
	if (!Layer::init())
		return false;

	m_isRunning = false;

	auto UI = CSLoader::createNode("Tollgates/BOSS2ZerglingNinja.csb");
	addChild(UI);

	m_controlLayer = TollgateControlLayer::create();
	m_controlLayer->initTimeBar();
	m_controlLayer->scheduleUpdate();
	addChild(m_controlLayer);



	return true;
}

bool BOSS2ZerglingNinja::onTouchBegan()
{
	
	return true;
}