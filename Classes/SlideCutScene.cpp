//SlideCutScene
#include"SlideCutScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include "TollgateControlLayer.h"

const int diff0 = 9;
const int diff1 = 11;
const int diff2 = 12;
const int diff3 = 13;
const int diff4 = 14;

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;


Scene* SlideCutScene::createScene(int diff, int loop)
{
	auto scene = Scene::create();
	auto layer = SlideCutScene::create(diff, loop);
	scene->addChild(layer);
	return scene;
}

bool SlideCutScene::init(int diff, int loop)
{
	if (!Layer::init())
		return false;
	auto winSize = Director::getInstance()->getWinSize();

	auto UI = CSLoader::createNode("Tollgates/SlideCutScene.csb");
	addChild(UI);

	m_controlLayer = TollgateControlLayer::create();
	m_controlLayer->initTimeBar();
	m_controlLayer->scheduleUpdate();
	addChild(m_controlLayer);

	m_grid = SlideCutGrid::create(diff, loop);
	m_grid->setPosition(0, 0);
	this->addChild(m_grid);

	return true;
}

Layer* SlideCutScene::create(int diff, int loop)
{
	auto pRef = new SlideCutScene();
	if(pRef && pRef->init(diff, loop))
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

void SlideCutScene::update()
{

}

/*
Slide Cut Grid
*/

SlideCutGrid* SlideCutGrid::create(int diff, int loop, int row, int col)
{
	auto pRef = new SlideCutGrid();
	if (pRef && pRef->init(diff, loop, row, col))
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

bool SlideCutGrid::init(int diff, int loop, int row, int col)
{
	if (!Layer::init())
		return false;

	m_row = row;
	m_col = col;
	m_loop = loop;
	m_diff = diff;
	m_isRunning = false;

	// 根据行、列，初始化一个空的二维容器
	m_farmerGrid.resize(m_col);
	for (auto &vec : m_farmerGrid)
		vec.resize(m_row);


	// 流星拖尾MotionStreak
	streak = MotionStreak::create(0.5f, 50, 10, Color3B::WHITE, "Res/Workers/blade.png");
	//    streak = MotionStreak::create(0.5f, 1, 10, Color3B::RED, "steak.png");
	streak->setPosition(0,0); // 设置拖尾streak的位置
	this->addChild(streak);

	generateNewFarmersGrid(m_diff);

	//创建一个事件监听器类型为 单点触摸
	auto touchListener = EventListenerTouchOneByOne::create();

	//绑定事件
	touchListener->onTouchBegan = CC_CALLBACK_2(SlideCutGrid::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(SlideCutGrid::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SlideCutGrid::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	
	return true;
}

//单点触摸事件响应函数
bool SlideCutGrid::onTouchBegan(Touch *touch, Event *unused_event)
{
	Vec2 Spos = touch->getLocation();
	streak->setPosition(Spos);
	// 删除所有活动条带段
	streak->reset();

	auto pos = touch->getLocation();
	pos = convertToGridPos(pos);
	int x1 = (int)pos.x;
	int y1 = (int)pos.y;
	log("x = %d, y = %d", x1, y1);
	return true;
}
void SlideCutGrid::onTouchMoved(Touch *touch, Event *unused_event)
{ 
	if (!m_isRunning)
	{
		m_isRunning = true;
		TimeManager::getInstance()->startCountDown();
	}
	// 触摸移动的偏移量
	Vec2 delta = touch->getDelta();
	auto Spos = touch->getLocation();
	// 设置位置
	streak->setPosition(Spos+delta);


	auto pos = touch->getLocation();
	pos = convertToGridPos(pos);


	int x1 = (int)pos.x;
	int y1 = (int)pos.y;
	if ((0 <= x1 && x1 < 10) && (0 <= y1 && y1 < 6) && m_farmerGrid[x1][y1])
	{
		// 如果倒计时还没有开始，则开始倒计时
		if (!m_isRunning)
		{
			m_isRunning = true;
			TimeManager::getInstance()->startCountDown();
		}
		// * add animation
		auto farmer = m_farmerGrid[x1][y1];
		log("farmer pos x = %f, y = %f", farmer->getPosition().x, farmer->getPosition().y);
		// 清空矩阵中的狗的指针
		m_farmerGrid[x1][y1] = nullptr;
		// 将狗从矩阵的绘制节点中移除
		farmer->tapped();
		// 如果狗被消光，但是loop>0
		if (getLivingFarmersNum() == 0 && m_loop > 0)
		{
			generateNewFarmersGrid(m_diff);
		}
		else if(getLivingFarmersNum() <= 0 && m_loop <= 0)
		{
			_eventDispatcher->dispatchCustomEvent("tollgate_clear", (void*)"SlideCut");
			CCLOG("SlideCut clear");
		}
	}
}
void SlideCutGrid::onTouchEnded(Touch *touch, Event *unused_event)     {  }


void SlideCutGrid::setFarmerPixPos(Farmer* farmer, int x, int y)
{
	farmer->setPosition(x * Grid_WIDTH + Left_MARGIN, y * Grid_WIDTH + Bottom_MARGIN);
}

Farmer* SlideCutGrid::createAFarmer(int type , int x, int y)
{
	Farmer * farmer = nullptr;
	if (type == 0)
		return nullptr;
	farmer = Farmer::FarmerAppear(type);
	setFarmerPixPos(farmer, x, y);
	addChild(farmer);

	return farmer;
}

Vec2 SlideCutGrid::convertToGridPos(cocos2d::Vec2 pixPos)
{
	float x, y;
	
	x = (pixPos.x - Left_MARGIN) / Grid_WIDTH;
	y = (pixPos.y - Bottom_MARGIN) / Grid_WIDTH;
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
void SlideCutGrid::generateNewFarmersGrid(const int diff)
{
	m_loop--;
	int sum = 0;
	if (m_diff == 0 || m_diff == 1)
	{
		sum = random(diff0, diff1);
	}
	else if (m_diff == 2)
	{
		sum = random(diff0, diff2);
	}
	else if (m_diff == 3)
	{
		sum = random(diff0, diff3);
	}
	else
	{
		sum = random(diff0, diff4);
	}
	int t = random(1, 3);
	int x = random(0, 9);
	int y = random(0, 5);
	for (int i = 0; i < sum; i++)
	{
		for (; m_farmerGrid[x][y] != 0;)
		{
			t = random(1, 3);
			x = random(0, 9);
			y = random(0, 5);
		}
		m_farmerGrid[x][y] = createAFarmer(t, x, y);
	}
}
/*
void SlideCutGrid::generateNewFarmersGrid(const int diff)
{
	m_loop--;
	int r = random(1, 3);
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			if (m_a[0][y][x] != 0)
				m_farmerGrid[x][y] = createAFarmer(r, x, y);
		}
	}
	log("loop=%d", m_loop);
}*/
int SlideCutGrid::getLivingFarmersNum()
{
	int count = 0;
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			if (m_farmerGrid[x][y] != nullptr)
				count++;
		}
	}
	return count;
}