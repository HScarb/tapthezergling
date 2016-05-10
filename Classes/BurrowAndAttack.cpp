//FeedzerglingScene
#include "BurrowAndAttack.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include "TollgateControlLayer.h"
#include"math.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace cocos2d;


Scene* FeedZerglingScene::createScene(int diff, int loop)
{
	auto scene = Scene::create();
	auto layer = FeedZerglingScene::create(diff, loop);
	scene->addChild(layer);
	return scene;
}
bool FeedZerglingScene::init(int diff, int loop)
{
	if (!Layer::init())
		return false;
	auto winSize = Director::getInstance()->getWinSize();

	auto UI = CSLoader::createNode("Tollgates/FeedZerglingScene.csb");
	addChild(UI);

	m_controlLayer = TollgateControlLayer::create();
	m_controlLayer->initTimeBar();
	m_controlLayer->scheduleUpdate();
	addChild(m_controlLayer);

	m_grid = FeedZerglingGrid::create(diff, loop);
	m_grid->setPosition(0, 0);
	this->addChild(m_grid);

	return true;
}
Layer* FeedZerglingScene::create(int diff, int loop)
{
	auto pRef = new FeedZerglingScene();
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
void FeedZerglingScene::update()
{

}
/*
Feed Zergling Grid
*/

FeedZerglingGrid* FeedZerglingGrid::create(int diff, int loop, int row, int col)
{
	auto pRef = new FeedZerglingGrid();
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
bool FeedZerglingGrid::init(int diff, int loop, int row, int col)
{
	if (!Layer::init())
		return false;

	m_row = row;
	m_col = col;
	m_loop = loop;
	m_diff = diff;
	m_isRunning = false;

	// 根据行、列，初始化一个空的二维容器
	m_foodGrid.resize(m_col);
	for (auto &vec : m_foodGrid)
		vec.resize(m_row);

	m_zergling = Sprite::create("Res/zergling_small_1.png");
	m_zergling->setPosition(480, 320);
	this->setAnchorPoint(Vec2(0, 0));// 设置锚点为左下角
	this->addChild(m_zergling);

	// 流星拖尾MotionStreak
	streak = MotionStreak::create(0.5f, 50, 10, Color3B::WHITE, "Res/Workers/blade.png");
	//    streak = MotionStreak::create(0.5f, 1, 10, Color3B::RED, "steak.png");
	streak->setPosition(0, 0); // 设置拖尾streak的位置
	this->addChild(streak);

	generateVisualizationFoodGrid(m_diff);

	//创建一个事件监听器类型为 单点触摸
	auto touchListener = EventListenerTouchOneByOne::create();

	//绑定事件
	touchListener->onTouchBegan = CC_CALLBACK_2(FeedZerglingGrid::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(FeedZerglingGrid::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(FeedZerglingGrid::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}
bool FeedZerglingGrid::onTouchBegan(Touch *touch, Event *unused_event)
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
void FeedZerglingGrid::onTouchMoved(Touch *touch, Event *unused_event)
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
	streak->setPosition(Spos + delta);
	auto pos = touch->getLocation();
	pos = convertToGridPos(pos);
	int x1 = (int)pos.x;
	int y1 = (int)pos.y;
	if ((0 <= x1 && x1 < 10) && (0 <= y1 && y1 < 6))
	{
		// 如果倒计时还没有开始，则开始倒计时
		if (!m_isRunning)
		{
			m_isRunning = true;
			TimeManager::getInstance()->startCountDown();
		}

		//控制狗移动
		if (abs(delta.x) > abs(delta.y))
		{
			if (delta.x > 0)
			{
				MoveTo *moveto = MoveTo::create(0.1f, Point(120, 0));
				m_zergling->runAction(moveto);
			}
			if (delta.x < 0)
			{
				MoveBy *moveby = MoveBy::create(0.1f, Point(120, 0));
			}
		}
		else
		{
			if (delta.y > 0)
			{
				MoveTo *moveto = MoveTo::create(0.1f, Point(0, 120));
				m_zergling->runAction(moveto);
			}
			if (delta.y < 0)
			{
				MoveBy *moveby = MoveBy::create(0.1f, Point(0, 120));
			}

		}
		if (m_zergling && m_foodGrid[x1][y1])
		{
			// * add animation
			auto food = m_foodGrid[x1][y1];
			log("farmer pos x = %f, y = %f", food->getPosition().x, food->getPosition().y);
			// 清空矩阵中的狗的指针
			m_foodGrid[x1][y1] = nullptr;
			// 将狗从矩阵的绘制节点中移除
			food->tapped();
			// 如果狗被消光，但是loop>0
			if (getVisualizationFoodNum() == 0 && m_loop > 0)
			{
				generateVisualizationFoodGrid(m_diff);
			}
			else if (getVisualizationFoodNum() <= 0 && m_loop <= 0)
			{
				//_eventDispatcher->dispatchCustomEvent("tollgate_clear", (void*)"SlideCut");
				//CCLOG("SlideCut clear");
			}
		}
	}
}
void FeedZerglingGrid::onTouchEnded(Touch *touch, Event *unused_event)     {  }


void FeedZerglingGrid::setFoodPixPos(Food* food, int x, int y)
{
	food->setPosition(x * GRID_Width + LEFT_Margin, y + GRID_Width + BOTTOM_Margin);
}

Food* FeedZerglingGrid::createTFood(Food::Foodtype type, int x, int y)
{
	Food * food = nullptr;
	if (type == 0)
		return nullptr;
	food = Food::createByType(type);
	setFoodPixPos(food, x, y);
	addChild(food);

	return food;
}

Vec2 FeedZerglingGrid::convertToGridPos(cocos2d::Vec2 pixPos)
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
void FeedZerglingGrid::generateVisualizationFoodGrid(const int diff)
{
	m_loop--;
	int r = random(1, 3);
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			if (m_f[0][y][x] != 0)
				m_foodGrid[x][y] = createTFood((Food::Foodtype)m_f[diff][y][x], x, y);
		}
	}
	log("loop=%d", m_loop);
}
int FeedZerglingGrid::getVisualizationFoodNum()
{
	int count = 0;
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			if (m_foodGrid[x][y] != nullptr)
				count++;
		}
	}
	return count;
}
