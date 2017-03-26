//BurrowAndAttack
#include"BurrowAndAttack.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include"TimeManager.h"
#include"TollgateControlLayer.h"
#include"math.h"
#include "Global.h"
#include "GameManager.h"

const int diff0 = 1;
const int diff1 = 2;
const int diff2 = 3;
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

Scene* BurrowAndAttackScene::createScene(int diff, int loop)
{
	auto scene = Scene::create();
	auto layer = BurrowAndAttackScene::create(diff, loop);
	scene->addChild(layer);
	return scene;
}

bool BurrowAndAttackScene::init(int diff, int loop)
{
	if (!Layer::init())
	{
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();

	auto UI = CSLoader::createNode("Tollgates/BurrowAndAttack.csb");
	addChild(UI);

	m_controlLayer = TollgateControlLayer::create();
	m_controlLayer->initTimeBar();
	m_controlLayer->scheduleUpdate();
	addChild(m_controlLayer, ZORDER_TOLLGATECONTROLLAYER);

	m_grid = BurrowAndAttackGrid::create(diff, loop);
	m_grid->setPosition(0, 0);
	this->addChild(m_grid);
	return true;
}

Layer *BurrowAndAttackScene::create(int diff, int loop)
{
	auto pRef = new BurrowAndAttackScene();
	if (pRef&&pRef->init(diff, loop))
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
void BurrowAndAttackScene::update()
{

}
/*
Burrow And Attack Grid
*/

BurrowAndAttackGrid* BurrowAndAttackGrid::create(int diff, int loop, int row, int col)
{
	auto pRef = new BurrowAndAttackGrid();
	if (pRef&&pRef->init(diff, loop, row, col))
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

bool BurrowAndAttackGrid::init(int diff, int loop, int row, int col)
{
	if (!Layer::init())
		return false;

	m_row = row;
	m_col = col;
	m_loop = loop;
	m_diff = diff;
	m_isRunning = false;
	//根据行列初始化一个空的二维容器
	m_workergrid.resize(m_col);
	for (auto &vec : m_workergrid)
		vec.resize(m_col);

	//随机出现一只狗
	int x = random(0, 5);
	int y = random(0, 2);
	for (; m_workergrid[x][y] != 0;)
	{
		x = random(0, 5);
		y = random(0, 2);
	}
	m_zergling = createAZerglingWithZOrder(7, x, y, 2);
	//根据难度来创建关卡内容
	generateNewWorkerGrid(m_diff);

	
	

	//创建一个时间监听器类型为单点触控
	auto touchListener = EventListenerTouchOneByOne::create();

	//绑定事件
	touchListener->onTouchBegan = CC_CALLBACK_2(BurrowAndAttackGrid::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(BurrowAndAttackGrid::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(BurrowAndAttackGrid::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}

//单点触摸事件响应函数
bool BurrowAndAttackGrid::onTouchBegan(Touch* touch, Event* unused_event)
{
	if (!m_isRunning)
	{
		m_isRunning = true;
		TimeManager::getInstance()->startCountDown();
	}
	m_Bpos = touch->getLocation();
	
	return true;
}
void BurrowAndAttackGrid::onTouchMoved(Touch* touch, Event* unused_event){}
void BurrowAndAttackGrid::onTouchEnded(Touch* touch, Event* unused_event)
{
	m_Epos = touch->getLocation();
	//触摸运动偏移量
	m_delta.x = abs(m_Bpos.x - m_Epos.x);
	m_delta.y = abs(m_Bpos.y - m_Epos.y);
	auto zpos = m_zergling->getPosition();
	zpos = convertToGridPos(zpos);
	int x1 = (int)zpos.x;
	int y1 = (int)zpos.y;
	auto pos = m_zergling->getPosition();
	if ((x1 >= 0 && x1 < 6) && (y1 >= 0 && y1<3))
	{
		MoveTo *moveto = nullptr;
		
		if ((abs(m_delta.x)) >(abs(m_delta.y)))
		{
			if ((m_Bpos.x - m_Epos.x) < 0)
			{
				if (x1 != 5)
				{
					moveto = MoveTo::create(0.1f, Point(pos.x + GRID_Width, pos.y));
					//m_zergling->runAction(moveto);
				}
				
			}
			else
			{
				if (x1 != 0)
				{
					moveto = MoveTo::create(0.1f, Point(pos.x - GRID_Width, pos.y));
					//m_zergling->runAction(moveto);
				}
			}
		}
		else if ((abs(m_delta.x)) < (abs(m_delta.y)))
		{
			if ((m_Bpos.y - m_Epos.y) < 0)
			{
				if (y1 != 2)
				{
					moveto = MoveTo::create(0.1f, Point(pos.x, pos.y + GRID_Width));
					//m_zergling->runAction(moveto);
				}
				
			}
			else
			{
				if (y1 != 0)
				{
					moveto = MoveTo::create(0.1f, Point(pos.x, pos.y - GRID_Width));
					//m_zergling->runAction(moveto);
				}
			}
		}
		CallFunc * moveEndCall = CallFunc::create([&]()
		{
			auto Zpos = m_zergling->getPosition();
			Zpos = convertToGridPos(Zpos);
			int x2 = (int)Zpos.x;
			int y2 = (int)Zpos.y;
			if (m_workergrid[x2][y2])
			{

				// * add animation
				auto worker = m_workergrid[x2][y2];
				// 清空矩阵中的狗的指针
				m_workergrid[x2][y2] = nullptr;
				// 将狗从矩阵的绘制节点中移除
				worker->tapped();
				if (getLivingWorkerNum() == 0 && m_loop > 0)
				{
					generateNewWorkerGrid(0);
				}
				else if (getLivingWorkerNum() <= 0 && m_loop <= 0)
				{
					_eventDispatcher->dispatchCustomEvent("tollgate_clear", (void*)"BurrowAndAttack");					
					CCLOG("BurrowAndAttack clear");
				}
			}
		});
		if (moveto)
			m_zergling->runAction(Sequence::create(moveto, moveEndCall, nullptr));
		
	}
}



void BurrowAndAttackGrid::SetZerglingPixPos(Worker* worker, int x, int y)
{
	worker->setPosition(x* GRID_Width + LEFT_Margin, y*GRID_Width + BOTTOM_Margin);
}
void BurrowAndAttackGrid::SetWorkerPixPos(Worker* worker, int x, int y)
{
	worker->setPosition(x* GRID_Width + LEFT_Margin + 25, y*GRID_Width + BOTTOM_Margin + 25);
}


Worker* BurrowAndAttackGrid::createAWorker(int type, int x, int y)
{
	Worker* worker = nullptr;
	if (type == 0)
	{
		return nullptr;
	}
	worker = Worker::Workertype(type);
	SetWorkerPixPos(worker, x, y);
	addChild(worker);
	return worker;
}

Worker* BurrowAndAttackGrid::createAZerglingWithZOrder(int type, int x, int y, int ZOrder)
{
	Worker* worker = nullptr;
	if (type == 0)
	{
		return nullptr;
	}
	worker = Worker::Workertype(type);
	SetZerglingPixPos(worker, x, y);
	addChild(worker, ZOrder);
	return worker;
}

Vec2 BurrowAndAttackGrid::convertToGridPos(cocos2d::Vec2 pixPos)
{
	float x, y;
	x = (pixPos.x - LEFT_Margin) / GRID_Width;
	y = (pixPos.y - BOTTOM_Margin) / GRID_Width;
	if (x < 0.0)
	{
		x = -1.0;
	}
	if (y < 0.0)
	{
		y = -1.0;
	}
	return Vec2(x, y);
}

void BurrowAndAttackGrid::generateNewWorkerGrid(const int diff)
{
	m_loop--;
	auto Zpos = m_zergling->getPosition();
	Zpos = convertToGridPos(Zpos);
	int x1 = (int)Zpos.x;
	int y1 = (int)Zpos.y;
	int sum = 0;
	if (m_diff == 0)
	{
		sum = diff0;
	}
	else if (m_diff == 1)
	{
		sum = diff1;
	}
	else if (m_diff == 2)
	{
		sum = diff2;
	}
	int t = random(1, 3);
	int x = random(0, 5);
	int y = random(0, 2);
	for (int j = 0; j < sum; j++)
	{
		for (; m_workergrid[x][y] != 0;)
		{
			t = random(1, 3);
			x = random(0, 5);
			y = random(0, 2);
		}
		if (x == x1&&y == y1)
		{
			t = random(1, 3);
			x = random(0, 5);
			y = random(0, 2);
		}
		m_workergrid[x][y] = createAWorker(t, x, y);
	}
}
int BurrowAndAttackGrid::getLivingWorkerNum()
{
	int count = 0;
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			if (m_workergrid[x][y] != nullptr)
				count++;
		}
	}
	return count;
}