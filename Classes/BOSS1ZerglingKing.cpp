// BOSS1ZerglingKing.cpp
#include "BOSS1ZerglingKing.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include "AnimationUtil.h"
#include "Shake.h"
using namespace std;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
USING_NS_CC;

cocos2d::Scene* BOSS1ZerglingKing::createScene()
{
	auto scene = Scene::create();
	auto layer = BOSS1ZerglingKing::create();
	scene->addChild(layer);
	return scene;
}

bool BOSS1ZerglingKing::init()
{
	if (!Layer::init())
		return false;

	m_isRunning = false;
	m_hitPoint = TOUCH_SUM;

	auto UI = CSLoader::createNode("Tollgates/BOSS1ZerglingKing.csb");
	addChild(UI);

	m_controlLayer = TollgateControlLayer::create();
	m_controlLayer->initTimeBar();
	m_controlLayer->scheduleUpdate();
	addChild(m_controlLayer);

	// Ìí¼Ó¹·µÄ¶¯»­
	auto visibleSize = Director::getInstance()->getVisibleSize();
	m_zerglingKing = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("zergling_big_1.png"));
	m_zerglingKing->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 200);
	m_zerglingKing->setAnchorPoint(Vec2(0.5f, 0));
	m_zerglingKing->setScale(0.4, 0.4);
	this->addChild(m_zerglingKing);
	Animation * animation = AnimationUtil::createWithFrameNameAndNum("zergling_big_", 4, 0.08f, -1, true);
	m_zerglingKing->runAction(Animate::create(animation));

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(BOSS1ZerglingKing::onTouchesBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void BOSS1ZerglingKing::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* unused_event)
{
	for(auto &item: touches)
	{
		Touch * touch = item;
		Vec2 pos = touch->getLocation();
		if(m_zerglingKing->getBoundingBox().containsPoint(pos))
		{
			if(!m_isRunning)
			{
				m_isRunning = true;
				TimeManager::getInstance()->startCountDown();
			}
			m_hitPoint--;
			auto shake = CCShake::create(0.2, 10);
			m_zerglingKing->runAction(shake);
			m_zerglingKing->setScale(m_zerglingKing->getScale() * 0.95);
			if(m_hitPoint <= 0)
			{
				_eventDispatcher->dispatchCustomEvent("tollgate_clear", (void*)"BOSS1ZerglingKing");
				CCLOG("BOSS1 ZerglingKing clear");
			}
		}
	}
}