//EacFlowersScnen.cpp
#include "EatFlowersScene.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include "Flower.h"
#include "TollgateControlLayer.h"
#include "AnimationUtil.h"
#include "Global.h"
#include "GameManager.h"

USING_NS_CC;

using namespace std;
using namespace ui;
using namespace cocostudio::timeline;
using namespace CocosDenshion;

Scene* EatFlowersScene::createScene(int diff, int loop)
{
	auto scene = Scene::create();
	auto layer = EatFlowersScene::create(diff, loop);
	scene->addChild(layer);
	return scene;
}

bool EatFlowersScene::init(int diff, int loop)
{
	if (!Layer::init())
		return false;

	place = 0;
	m_diff = diff;
	m_loop = loop;
	m_flower = nullptr;
	m_isRunning = false;

	auto UI = CSLoader::createNode("Tollgates/EatFlowersScene.csb");
	addChild(UI);

	m_controlLayer = TollgateControlLayer::create();
	m_controlLayer->initTimeBar();
	m_controlLayer->scheduleUpdate();
	addChild(m_controlLayer, ZORDER_TOLLGATECONTROLLAYER);

	m_pauseBtn = (Button*)(UI->getChildByName("Button_pause"));
	m_timeBar = (LoadingBar*)(UI->getChildByName("LoadingBar_time"));
	m_timeText = (Text*)(UI->getChildByName("Text_time"));

	m_Vec2Vec.push_back(Vec2(200, 40)); 
	m_Vec2Vec.push_back(Vec2(340, 40));
	m_Vec2Vec.push_back(Vec2(480, 40));
	m_Vec2Vec.push_back(Vec2(620, 40));
	m_Vec2Vec.push_back(Vec2(760, 40));
	m_Vec2Vec.push_back(Vec2(200, 190));
	m_Vec2Vec.push_back(Vec2(340, 190));
	m_Vec2Vec.push_back(Vec2(480, 190));
	m_Vec2Vec.push_back(Vec2(620, 190));
	m_Vec2Vec.push_back(Vec2(760, 190));
	m_Vec2Vec.push_back(Vec2(200, 340));
	m_Vec2Vec.push_back(Vec2(340, 340));
	m_Vec2Vec.push_back(Vec2(480, 340));
	m_Vec2Vec.push_back(Vec2(620, 340));
	m_Vec2Vec.push_back(Vec2(760, 340));

	for (int n = 0; n < 15; n++)
	{
		is_occupy[n] = 0;
	}

	for (int n = 0; n < 3; n++)
	{
		int i = random(1, 4);
		do
		{
			place = random(0, 14);
		} while (is_occupy[place] == 1);
		is_occupy[place] = 1;
		m_flower = Sprite::create(StringUtils::format("res/Res/flower/flower_%d.png", i));
		m_flowerVec.pushBack(m_flower);
		m_flower->setPosition(m_Vec2Vec.at(place));
		this->addChild(m_flower);
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchEnded = CC_CALLBACK_2(EatFlowersScene::onTouchEnded, this);
	listener->onTouchBegan = CC_CALLBACK_2(EatFlowersScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

cocos2d::Layer* EatFlowersScene::create(int diff, int loop)
{
	auto pRef = new EatFlowersScene();
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

void EatFlowersScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

bool EatFlowersScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	auto pos = touch->getLocation();
	int x1 = (int)pos.x;
	int y1 = (int)pos.y;
	
	if (!m_isRunning)
	{
		m_isRunning = true;
		TimeManager::getInstance()->startCountDown();
	}

	for (auto item : m_flowerVec)
	{
		int p = 0;
		if (item->getBoundingBox().containsPoint(pos))
		{
			int k = p;
			item->removeFromParent();
			PLAY_BURST_ANIMATION(item->getPosition(), 0.8f);
			m_flowerVec.eraseObject(item);
			is_occupy[k] = 0;   //重置是否占用坐标位置
		}
		p++;
	}
	int m = m_loop;
	if (m_flowerVec.size() <= 0 && m_loop <= 0) //初始的设置为m_loop = 0
	{
		_eventDispatcher->dispatchCustomEvent("tollgate_clear", (void*)"EatFlowers");
		CCLOG("EatFlowers clear");
	}
	else if (m_flowerVec.size() > 0 && m_loop > 0)
	{
		int i = random(1, 4);
		do
		{
			place = random(0, 14);
		}
		while (is_occupy[place] == 1);
		is_occupy[place] = 1;
		m_flower = Sprite::create(StringUtils::format("res/Res/flower/flower_%d.png", i));
		m_flowerVec.pushBack(m_flower);
		m_flower->setPosition(m_Vec2Vec.at(place));
		m_flower->setScale(0.0);
		m_flower->runAction(ScaleTo::create(0.25, 1.0));
		this->addChild(m_flower);

		m_loop--;
	}
	return true;
}
