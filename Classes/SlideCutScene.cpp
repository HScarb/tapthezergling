//SlideCutScene
#include"SlideCutScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace cocos2d;



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
	m_controlLayer = CSLoader::createNode("Tollgates/TollgateControlLayer.csb");
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
	m_isRunning = false;
	m_touchesLabel = Label::create("0000", "Arial", 30);
	m_touchesLabel->setPosition(100, 500);
	this->addChild(m_touchesLabel);

	// 根据行、列，初始化一个空的二维容器
	m_farmerGrid.resize(m_col);
	for (auto &vec : m_farmerGrid)
		vec.resize(m_row);

	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			m_farmerGrid[x][y] = createAFarmer((Farmer::Farmerappear)m_a[0][y][x], x, y);
		}
	}

	//创建一个事件监听器类型为 单点触摸
	auto touchListener = EventListenerTouchOneByOne::create();

	//绑定事件
	touchListener->onTouchBegan = CC_CALLBACK_2(SlideCutGrid::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(SlideCutGrid::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SlideCutGrid::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	/*auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event *event){};
	listener->onTouchMoved = [*](Touch* touch, Event *event)
	{
		if (!m_isRunning)
		{
			m_isRunning = true;
			TimeManager::getInstance()->startCountDown();
		}
		auto pos = touch->getLocation();
		pos.x /= Grid_WIDTH;
		pos.y /= Grid_WIDTH;
		int x1 = (int)pos.x - 1;
		int y1 = (int)pos.y - 1;
		if ((0 <= x1 && x1 <8 ) && (0 <= y1 && y1 < 6)&&m_farmerGrid[x1][y1])
		{
			log("crush!");
			// * add animation
			auto farmer = m_farmerGrid[x1][y1];
			// 清空矩阵中的狗的指针
			m_farmerGrid[x1][y1] = nullptr;
			// 将狗从矩阵的绘制节点中移除
			farmer->tapped();
		}

	};
	listener->onTouchEnded = [=](Touch* touch, Event *event){

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);*/

	return true;
}

//单点触摸事件响应函数
bool SlideCutGrid::onTouchBegan(Touch *touch, Event *unused_event)
{
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
	auto pos = touch->getLocation();
	pos = convertToGridPos(pos);
	int x1 = (int)pos.x;
	int y1 = (int)pos.y;
	if ((0 <= x1 && x1 < 10) && (0 <= y1 && y1 < 6) && m_farmerGrid[x1][y1])
	{
		// * add animation
		auto farmer = m_farmerGrid[x1][y1];
		log("farmer pos x = %f, y = %f", farmer->getPosition().x, farmer->getPosition().y);
		// 清空矩阵中的狗的指针
		m_farmerGrid[x1][y1] = nullptr;
		// 将狗从矩阵的绘制节点中移除
		farmer->tapped();
	}
}
void SlideCutGrid::onTouchEnded(Touch *touch, Event *unused_event)     { CCLOG("ended"); }


void SlideCutGrid::setFarmerPixPos(Farmer* farmer, int x, int y)
{
	farmer->setPosition(x * Grid_WIDTH + Left_MARGIN, y * Grid_WIDTH + Bottom_MARGIN);
}

Farmer* SlideCutGrid::createAFarmer(Farmer::Farmerappear appear , int x, int y)
{
	Farmer * farmer = nullptr;
	if (appear == 0)
		return nullptr;
	farmer = Farmer::FarmerAppear(appear);
	setFarmerPixPos(farmer, x, y);
	addChild(farmer);

	return farmer;
}

Vec2 SlideCutGrid::convertToGridPos(cocos2d::Vec2 pixPos)
{
	float x, y;
	x = (pixPos.x - Left_MARGIN) / Grid_WIDTH;
	y = (pixPos.y - Bottom_MARGIN) / Grid_WIDTH;
	return Vec2(x, y);
}