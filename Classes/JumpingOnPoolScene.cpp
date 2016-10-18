// JunpingOnPool.cpp
#include "JumpingOnPoolScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include "Global.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
const float DURATION = 0.24f;

Pool* Pool::create(bool isEnd)
{
	Pool * pRef = new Pool();
	if(pRef)
	{
		if(isEnd)	// 结束pool
		{
			pRef->m_isEnd = true;
			if(pRef->initWithFile("Res/star crafts/SCs_Doodad_rock_brown02.png"))
			{
				pRef->autorelease();
				return pRef;
			}
		}
		else		// 一般pool
		{
			if(pRef->initWithFile("Res/star crafts/SCs_Doodad_SteppingStone4.png"))
			{
				pRef->autorelease();
				return pRef;
			}
		}
	}
	CC_SAFE_DELETE(pRef);
	return nullptr;
}

cocos2d::Vec2 Pool::convertToPos()
{
	float x, y;
	int tempRow = 4 - m_row;
	y = -(tempRow * INTERVAL);
	x = (y - 300) / 5;
	if (m_dir == 1)
		x = -x;
	x += 480;
	y += 400;
	return cocos2d::Vec2(x, y);
}

Scene* JumpingOnPoolScene::createScene(int diff, int loop) 
{
	auto scene = Scene::create();
	auto layer = JumpingOnPoolScene::create(diff, loop);
	scene->addChild(layer);
	return scene;
}

bool JumpingOnPoolScene::init(int diff, int loop) 
{
	if (!Layer::init())
		return false;
	
	m_diff = diff;
	m_loop = loop;
	m_isRunning = false;
	m_isMoving = false;
	m_smallZergling = nullptr;
	
	auto UI = CSLoader::createNode("Tollgates/JumpingOnPoolScene.csb");
	addChild(UI);

	m_controlLayer = TollgateControlLayer::create();
	m_controlLayer->initTimeBar();
	m_controlLayer->scheduleUpdate();
	addChild(m_controlLayer, ZORDER_TOLLGATECONTROLLAYER);

	
	// 创建狗
	m_smallZergling = SmallZergling::create();
	m_smallZergling->setPosition(CENTER);
	this->addChild(m_smallZergling,5);
	m_smallZergling->idle();

	// 初始化pool和狗
	initPools(diff, loop);

	// 添加触摸监听
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(JumpingOnPoolScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

Layer* JumpingOnPoolScene::create(int diff, int loop) 
{
	auto pRef = new JumpingOnPoolScene();
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

void JumpingOnPoolScene::initPools(int diff, int loop)
{
	for (int i = 0; i < loop; i++)
	{
		addAGroupOfPools(diff);
	}
	if(m_poolVector.size() == 0)
	{
		// tollgate clear
	}
	else if(m_poolVector.size() <= 5)
	{
		// 如果里面剩下的小于5个，那全部拿出来放入显示的容器中，并且显示
		while (!m_poolVector.empty())
		{
			Pool * temp = m_poolVector.front();
			m_poolShowVector.pushBack(temp);
			m_poolVector.eraseObject(temp);
		}
	}
	else
	{
		// 如果剩下的大于5个，那就取出5个放到显示的容器中，并且显示
		int t = 5;
		while(t--)
		{
			Pool * temp = m_poolVector.front();
			m_poolShowVector.pushBack(temp);
			m_poolVector.eraseObject(temp);
		}
	}
	// 为显示容器中的Pool和zergling设置位置，并且显示
	for(auto item : m_poolShowVector)
	{
		item->setPosition(item->convertToPos());
		item->setScale(SCALE[item->getRow()]);
		this->addChild(item);
	}
	m_smallZergling->setPosition(m_poolShowVector.at(0)->getPosition());
	if (m_poolShowVector.at(0)->getDir() == 0)
		m_smallZergling->setScale(-1.0, 1.0);
}

void JumpingOnPoolScene::addAGroupOfPools(int diff)
{
	int sum = 0;	// pool的数量
	Pool * tempPool = nullptr;
	if(diff == 0)
	{
		sum = 4;
	}
	else if(diff == 1)
	{
		sum = random(4, 5);
	}
	else if(diff == 2)
	{
		sum = random(4, 6);
	}
	for (int i = 1; i <= sum;i++)
	{
		if(i == sum)
		{
			tempPool = Pool::create(true);
		}
		else if(i != sum)
		{
			tempPool = Pool::create(false);
		}
		tempPool->setRow(m_poolVector.size());	// 设置行数为当前容器的大小
		tempPool->setDir(random(0, 1));			// 随机左右
		m_poolVector.pushBack(tempPool);
	}
}

void JumpingOnPoolScene::movePools()
{
	m_isMoving = true;
	auto pPoolShowVector = &m_poolShowVector;

	// 添加新的pool进入场景
	if (!m_poolVector.empty())
	{
		CCLOG("Add a new pool into the scene.");
		Pool * temp = m_poolVector.front();
		m_poolShowVector.pushBack(temp);
		m_poolVector.eraseObject(temp);
		temp->setRow(5);
		temp->setPosition(temp->convertToPos());
		temp->setScale(0.2);
		this->addChild(temp);
	}

	for(auto item : m_poolShowVector)
	{
		item->setRow(item->getRow() - 1);
		if(item->getRow() >= 0)		// 如果不用移出屏幕外
		{
			auto moveTo = MoveTo::create(DURATION, item->convertToPos());
			auto scaleTo = ScaleTo::create(DURATION, 1.0 - 0.16 * item->getRow());
			item->runAction(Spawn::create(moveTo, scaleTo, nullptr));
		}
		else						// 如果要移出屏幕外
		{
			auto erase = CallFunc::create([pPoolShowVector, item, this]()
			{
				m_isMoving = false;
				m_poolShowVector.eraseObject(item);
				item->removeFromParent();

				if(m_poolVector.size() == 0 && m_poolShowVector.size() <= 1)
				{
					_eventDispatcher->dispatchCustomEvent("tollgate_clear", (void*)"JumpingOnPool");
					CCLOG("Jumping on pool clear");
				}
			});
			auto moveTo = MoveTo::create(DURATION, item->convertToPos());
			auto scaleTo = ScaleTo::create(DURATION, 1.0 - 0.16 * item->getRow());
			item->runAction(Sequence::create(Spawn::create(moveTo, scaleTo, nullptr), erase, nullptr));
		}
	}

	// 移动狗
	bool zerglingTurn = false;		// 是否要将zergling改变面向
	if(m_poolShowVector.size() >= 2)
	{
		if (m_poolShowVector.at(1)->getDir() != m_poolShowVector.at(0)->getDir())
			zerglingTurn = true;		// 反向
	}

	auto moveBy = MoveBy::create(DURATION, Vec2((280.0f * (m_poolShowVector.at(1)->getDir() - m_poolShowVector.at(0)->getDir())), 0));
	auto jump = JumpBy::create(DURATION, Vec2((280.0f * (m_poolShowVector.at(1)->getDir() - m_poolShowVector.at(0)->getDir())), 0), 100.0f, 1);
	auto call = CallFunc::create([this, zerglingTurn]()
	{
		if (zerglingTurn)
			m_smallZergling->setScale(-(m_smallZergling->getScaleX()), 1.0);		// 反向
		m_smallZergling->idle();
	});
	m_smallZergling->run();
	m_smallZergling->runAction(Sequence::create(jump, call, nullptr));
}

bool JumpingOnPoolScene::onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
	if (m_isMoving)
		return false;

	auto pos = pTouch->getLocation();
	
	if(!m_isRunning)
	{
		m_isRunning = true;
		TimeManager::getInstance()->startCountDown();
	}
	if(m_poolShowVector.size() <= 1)
	{
		// tollgate clear
	}
	else if(pos.x <= 480)
	{
		CCLOG("LEFT touch.");
		if(m_poolShowVector.at(1)->getDir() == 0)
		{
			movePools();
			// Zergling jump
		}
	}
	else if(pos.x > 480)
	{
		CCLOG("RIGHT touch.");
		if(m_poolShowVector.at(1)->getDir() == 1)
		{
			movePools();
			// zergling jump
		}
	}

	return true;
}