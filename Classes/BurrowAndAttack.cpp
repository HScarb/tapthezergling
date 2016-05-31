//BurrowAndAttack
#include"BurrowAndAttack.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include"TimeManager.h"
#include"TollgateControlLayer.h"
#include"math.h"

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
	addChild(m_controlLayer);

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

	//根据难度来创建关卡内容
	generateNewWorkerGrid(m_diff);

	//随机出现一只狗
	int x = random(0, 5);
	int y = random(0, 2);
	for (; m_workergrid[x][y] != 0;)
	{
		x = random(0, 5);
		y = random(0, 2);
	}
	/*m_zergling = Sprite::create("Res/zergling_small_7.png");
	m_zergling->setPosition(x* GRID_Width + LEFT_Margin, y*GRID_Width + BOTTOM_Margin);
	this->setAnchorPoint(Vec2(0, 0));// 设置锚点为左下角
	this->addChild(m_zergling,4);*/
	m_zergling = createAWorker(7, x, y);
	

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
void BurrowAndAttackGrid::onTouchMoved(Touch* touch, Event* unused_event)
{
	// 如果倒计时还没有开始，则开始倒计时
	if (!m_isRunning)
	{
		m_isRunning = true;
		TimeManager::getInstance()->startCountDown();
	}
	
}
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
		if ((abs(m_delta.x)) >(abs(m_delta.y)))
		{
			if ((m_Bpos.x - m_Epos.x) < 0)
			{
				if (x1 != 5)
				{
					MoveTo* moveto = MoveTo::create(0.2f, Point(pos.x + GRID_Width, pos.y));
					m_zergling->runAction(moveto);
				}
				
			}
			else
			{
				if (x1 != 0)
				{
					MoveTo* moveto = MoveTo::create(0.2f, Point(pos.x - GRID_Width, pos.y));
					m_zergling->runAction(moveto);
				}
			}
		}
		else if ((abs(m_delta.x)) < (abs(m_delta.y)))
		{
			if ((m_Bpos.y - m_Epos.y) < 0)
			{
				if (y1 != 2)
				{
					MoveTo* moveto = MoveTo::create(0.2f, Point(pos.x, pos.y + GRID_Width));
					m_zergling->runAction(moveto);
				}
				
			}
			else
			{
				if (y1 != 0)
				{
					MoveTo* moveto = MoveTo::create(0.2f, Point(pos.x, pos.y - GRID_Width));
					m_zergling->runAction(moveto);
				}
			}
		}
	}
	if ( m_workergrid[x1][y1])
	{
		
		// * add animation
		auto worker = m_workergrid[x1][y1];
		// 清空矩阵中的狗的指针
		m_workergrid[x1][y1] = nullptr;
		// 将狗从矩阵的绘制节点中移除
		worker->tapped();
		// 如果狗被消光，但是loop>0
		if (getLivingWorkerNum() == 0 && m_loop > 0)
		{
			generateNewWorkerGrid(m_diff);
		}
		else if (getLivingWorkerNum() <= 0 && m_loop <= 0)
		{
			_eventDispatcher->dispatchCustomEvent("tollgate_clear", (void*)"BurrowAndAttack");
			CCLOG("BurrowAndAttack clear");
		}
	}
}



void BurrowAndAttackGrid::SetWorkerPixPos(Worker* worker, int x, int y)
{
	worker->setPosition(x* GRID_Width + LEFT_Margin, y*GRID_Width + BOTTOM_Margin);
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
	int r = random(1, 3);
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			if (m_w[0][y][x] != 0)
				m_workergrid[x][y] = createAWorker(r, x, y);
		}
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