// BOSS2ZerglingNinja
#include "BOSS2ZerglingNinja.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include "AnimationUtil.h"
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
	m_posVector.push_back(Pt(Vec2(200, 40), 0));
	m_posVector.push_back(Pt(Vec2(480, 40), 1));
	m_posVector.push_back(Pt(Vec2(760, 40), 2));
	m_posVector.push_back(Pt(Vec2(200, 190), 3));
	m_posVector.push_back(Pt(Vec2(480, 190), 4));
	m_posVector.push_back(Pt(Vec2(760, 190), 5));
	m_posVector.push_back(Pt(Vec2(200, 340), 6));
	m_posVector.push_back(Pt(Vec2(480, 340), 7));
	m_posVector.push_back(Pt(Vec2(760, 340), 8));

	auto UI = CSLoader::createNode("Tollgates/BOSS2ZerglingNinja.csb");
	addChild(UI);

	m_controlLayer = TollgateControlLayer::create();
	m_controlLayer->initTimeBar();
	m_controlLayer->scheduleUpdate();
	addChild(m_controlLayer);

	// create wood
	int c;
	for(auto item : m_posVector)
	{
		Vec2 pos = item.pos;
		int r = random(1, 2);
		c = item.num;
		m_woods[c] = Sprite::create(StringUtils::format("star crafts/SCs_Doodad_log0%d.png", r));
		m_woods[c]->setScaleX(0.5);
		m_woods[c]->setScaleY(0.20);
		m_woods[c]->setPosition(pos);
		this->addChild(m_woods[c]);
	}

	// create zerging ninja
	auto visibleSize = Director::getInstance()->getVisibleSize();
	m_zerglingNinja = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("zergling_big_1.png"));
//	m_zerglingNinja->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 200);
//	m_curNum = random(0, (int)m_posVector.size());
	m_curPt = m_posVector.at(random(0, (int)m_posVector.size() - 1));
	m_zerglingNinja->setPosition(m_curPt.pos);

	m_zerglingNinja->setAnchorPoint(Vec2(0.5f, 0));
	m_zerglingNinja->setScale(0.15, 0.15);
	this->addChild(m_zerglingNinja);
	Animation * animation = AnimationUtil::createWithFrameNameAndNum("zergling_big_", 4, 0.08f, -1, true);
	m_zerglingNinja->runAction(Animate::create(animation));

	// add touch listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(BOSS2ZerglingNinja::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool BOSS2ZerglingNinja::onTouchBegan(Touch * pTouch, Event * pEvent)
{
	auto pos = pTouch->getLocation();
	if (m_zerglingNinja->getBoundingBox().containsPoint(pos))
	{
		if(!m_isRunning)
		{
			m_isRunning = true;
			TimeManager::getInstance()->startCountDown();
		}
//		m_posVector.erase(m_curPt);
		m_woods[m_curPt.num]->removeFromParent();
		for (auto iter = m_posVector.begin(); iter != m_posVector.end();)
		{
			if ((*iter) == m_curPt)
			{
				iter = m_posVector.erase(iter);
				// ²¥·Å±¬Õ¨¶¯»­
				Sprite * virtualBurstSprite = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("star crafts/starcrafts_SmallUnit_Death_1.png"));
				virtualBurstSprite->setPosition(m_curPt.pos.x, m_curPt.pos.y + 40);
				this->addChild(virtualBurstSprite);
				auto burst = AnimationUtil::createWithFrameNameAndNumRange("star crafts/starcrafts_SmallUnit_Death_", 1, 10, 1 / 12.0, 1, true);
				auto unShow = CallFunc::create([virtualBurstSprite]() {virtualBurstSprite->removeFromParent(); });
				virtualBurstSprite->runAction(Sequence::create(Animate::create(burst), unShow, nullptr));
			}
			else
			{
				++iter;
			}
		}
		// move to a new pos
		if(m_posVector.size() <= 0)
		{
			if (m_isRunning)
			{
				m_isRunning = false;
				auto drop = MoveTo::create(0.4, Vec2(m_zerglingNinja->getPositionX(), 20));
				auto stopTimer = CallFunc::create([&]()
				{
					TimeManager::getInstance()->pauseCountDown();
				});
				auto callback = CallFunc::create([&]()
				{
					m_zerglingNinja->removeFromParent();
					_eventDispatcher->dispatchCustomEvent("tollgate_clear", (void*)"BOSS2ZerglingNinja");
					CCLOG("BOSS2 ZerglingNinja clear");
				});
				auto sleep = DelayTime::create(0.2);
				m_zerglingNinja->runAction(Sequence::create(drop, stopTimer, sleep, callback, nullptr));
			}
		}
		else
		{
			m_curPt = m_posVector.at(random(0, (int)m_posVector.size() - 1));
			m_zerglingNinja->setScale(0.0);
			auto big = ScaleTo::create(0.15, 0.15);
			m_zerglingNinja->setPosition(m_curPt.pos);
			m_zerglingNinja->runAction(big);
		}
	}
	return true;
}