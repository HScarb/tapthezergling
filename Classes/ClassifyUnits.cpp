// ClassifyUnits.cpp
#include "ClassifyUnits.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include "Global.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
const float SCALE[5] = { 1.30,1.14,0.98,0.82,0.66 };
const int MAX_SHOW_NUM = 5;
const int INTERVAL = 50;
const Vec2 POS_TERRAN_BASE = Vec2(250, 100);
const Vec2 POS_ZERG_BASE = Vec2(250, 300);
const Vec2 POS_PROTOSS_BASE = Vec2(710, 100);
const Vec2 POS_SPAWNPOOL = Vec2(710, 300);
const float DURATION = 0.2;

Unit* Unit::create(UnitType type)
{
	auto bRet = new Unit();
	if(bRet && bRet->initWithType(type))
	{
		bRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(bRet);
	}
	return bRet;
}

bool Unit::initWithType(UnitType type)
{
	switch (type)
	{
	case NONE: 
		return false;
	case SCV: 
		if (!Sprite::initWithTexture(TextureCache::getInstance()->getTextureForKey(PATH_SCV_SMALL)))
			return false;
		break;
	case Drone: 
		if (!Sprite::initWithTexture(TextureCache::getInstance()->getTextureForKey(PATH_DRONE_SMALL)))
			return false;
		break;
	case Probe: 
		if (!Sprite::initWithTexture(TextureCache::getInstance()->getTextureForKey(PATH_PROBE_SMALL)))
			return false;
		break;
	case Zergling: 
		if (!Sprite::initWithTexture(TextureCache::getInstance()->getTextureForKey(PATH_ZERGLING_SMALL)))
			return false;
		break;
	default: break;
	}

	m_type = type;
	m_row = -1;

	return true;
}

cocos2d::Vec2 Unit::getPosByRow()
{
	float x = 480;
	int row = 5 - m_row;
	float y = 450 - row * INTERVAL;
	return Vec2(x, y);
}

Scene* ClassifyUnits::createScene(int diff, int loop)
{
	auto scene = Scene::create();
	auto layer = ClassifyUnits::create(diff, loop);
	scene->addChild(layer);
	return scene;
}

bool ClassifyUnits::init(int diff, int loop)
{
	if (!Layer::init())
		return false;
	
	m_diff = diff;
	m_loop = loop;
	m_isRunning = false;
	m_isMoving = false;

	auto UI = CSLoader::createNode("Tollgates/ClassifyUnits.csb");
	addChild(UI);
	
	m_controlLayer = TollgateControlLayer::create();
	m_controlLayer->initTimeBar();
	m_controlLayer->scheduleUpdate();
	this->addChild(m_controlLayer, ZORDER_TOLLGATECONTROLLAYER);

	// 创建Bases
	m_terranBase = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey(PATH_TERRAN_BASE));
	m_terranBase->setScale(0.25);
	m_terranBase->setPosition(POS_TERRAN_BASE);
	m_zergBase = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey(PATH_ZERG_BASE));
	m_zergBase->setScale(0.25);
	m_zergBase->setPosition(POS_ZERG_BASE);
	m_protossBase = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey(PATH_PROTOSS_BASE));
	m_protossBase->setPosition(POS_PROTOSS_BASE);
	m_protossBase->setScale(0.25);
	m_spawningPool = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey(PATH_SPAWNINGPOOL));
	m_spawningPool->setPosition(POS_SPAWNPOOL);
	m_spawningPool->setScale(0.5);

	addChild(m_terranBase, 100);
	addChild(m_zergBase, 100);
	addChild(m_protossBase, 100);
	addChild(m_spawningPool, 100);

	// 初始化Units
	initUnits();

	// 触摸监听
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ClassifyUnits::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

Layer* ClassifyUnits::create(int diff, int loop)
{
	auto pRet = new ClassifyUnits();
	if(pRet && pRet->init(diff, loop))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

void ClassifyUnits::initUnits()
{
	for (int i = 0; i < m_loop;i++)
	{
		addAGroupOfUnits();
	}
	if(m_unitVector.size() <= MAX_SHOW_NUM)	// 如果小于等于MAX个，全部显示
	{
		while(!m_unitVector.empty())
		{
			Unit * temp = m_unitVector.front();
			m_unitShowVector.pushBack(temp);
			m_unitVector.eraseObject(temp);
		}
	}
	else
	{
		int t = MAX_SHOW_NUM;
		while(t--)
		{
			Unit * temp = m_unitVector.front();
			m_unitShowVector.pushBack(temp);
			m_unitVector.eraseObject(temp);
		}
	}
	// 为容器中的Unit设置位置并且显示
	for(auto item : m_unitShowVector)
	{
		item->setPosition(item->getPosByRow());
		item->setScale(SCALE[item->getRow()]);
		this->addChild(item, 60 - item->getRow());
	}
}

void ClassifyUnits::addAGroupOfUnits()
{
	int sum = 0;
	if(m_diff == 0)
	{
		sum = 3;
	}
	else if(m_diff == 1)
	{
		sum = random(3, 4);
	}
	else if(m_diff == 2)
	{
		sum = random(3, 5);
	}
	for (int i = 1; i <= sum;i++)
	{
		Unit * temp = Unit::create((Unit::UnitType)random(1, 4));
		temp->setRow(m_unitVector.size());
		m_unitVector.pushBack(temp);
	}
}

void ClassifyUnits::moveUnits()
{
	m_isMoving = true;
	
	// 添加新的Unit进入场景
	if(!m_unitVector.empty())
	{
		Unit * unit = m_unitVector.front();
		int ZOrder = m_unitShowVector.back()->getZOrder();
		CCLOG("ZOrder = %d", ZOrder);
		m_unitShowVector.pushBack(unit);
		m_unitVector.eraseObject(unit);
		unit->setRow(5);
		unit->setPosition(unit->getPosByRow());
		unit->setScale(0.5);
		this->addChild(unit, ZOrder - 1);
	}
	// 移动Units
	for(auto item : m_unitShowVector)
	{
		item->setRow(item->getRow() - 1);
		if(item->getRow() >= 0)		// 如果不用飞走
		{
			auto moveTo = MoveTo::create(DURATION, item->getPosByRow());
			auto scaleTo = ScaleTo::create(DURATION, SCALE[item->getRow()]);
			item->runAction(Spawn::create(moveTo, scaleTo, nullptr));
		}
		else		// 如果要飞到基地里
		{
			auto erase = CallFunc::create([=] ()
			{
				m_isMoving = true;
				m_unitShowVector.eraseObject(item);
			});
			auto eraseend = CallFunc::create([=]()
			{
				item->removeFromParent();
				if(m_unitVector.size() == 0 && m_unitShowVector.size() == 0)
				{
					_eventDispatcher->dispatchCustomEvent("tollgate_clear", (void*)"ClassifyUnits");
					CCLOG("Classify units clear");
				}
			});
			JumpTo * jumpTo = nullptr;
			switch(item->getType())
			{
			case Unit::NONE: break;
			case Unit::SCV: 
				jumpTo = JumpTo::create(DURATION, POS_TERRAN_BASE, 100, 1);
				break;
			case Unit::Drone: 
				jumpTo = JumpTo::create(DURATION, POS_ZERG_BASE, 100, 1);
				break;
			case Unit::Probe: 
				jumpTo = JumpTo::create(DURATION, POS_PROTOSS_BASE, 100, 1);
				break;
			case Unit::Zergling: 
				jumpTo = JumpTo::create(DURATION, POS_SPAWNPOOL, 100, 1);
				break;
			default: break;
			}

			item->runAction(Sequence::create(erase, jumpTo, eraseend, nullptr));
		}
	}
}


bool ClassifyUnits::onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
	auto pos = pTouch->getLocation();
	if 
	(
		(m_terranBase->getBoundingBox().containsPoint(pos) && m_unitShowVector.front()->getType() == 1)
		||(m_zergBase->getBoundingBox().containsPoint(pos) && m_unitShowVector.front()->getType() == 2)
		||(m_protossBase->getBoundingBox().containsPoint(pos) && m_unitShowVector.front()->getType() == 3)
		||(m_spawningPool->getBoundingBox().containsPoint(pos) && m_unitShowVector.front()->getType() == 4)
	)
	{
		if(!m_isRunning)
		{
			m_isRunning = true;
			TimeManager::getInstance()->startCountDown();
		}
		moveUnits();
	}
	return true;
}