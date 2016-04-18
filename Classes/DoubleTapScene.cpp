// DoubleTapScene.cpp
#include "DoubleTapScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

Scene* DoubleTapScene::createScene(int diff, int loop)
{
	auto scene = Scene::create();
	auto layer = DoubleTapScene::create(diff, loop);
	scene->addChild(layer);
	return scene;
}

bool DoubleTapScene::init(int diff, int loop)
{
	if (!Layer::init())
		return false;
	
	auto winSize = Director::getInstance()->getWinSize();

	auto UI = CSLoader::createNode("Tollgates/DoubleTapScene.csb");
	addChild(UI);

	m_pauseBtn = (Button*)(UI->getChildByName("Button_pause"));
	m_timeBar = (LoadingBar*)(UI->getChildByName("LoadingBar_time"));
	m_timeText = (Text*)(UI->getChildByName("Text_time"));
	
	m_grid = DoubleTapGrid::create(diff, loop);
	m_grid->setPosition(120, 80);
	this->addChild(m_grid);

	return true;
}

cocos2d::Layer* DoubleTapScene::create(int diff, int loop)
{
	auto pRef = new DoubleTapScene();
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

/*
	Double Tap Grid
*/

DoubleTapGrid* DoubleTapGrid::create(int diff, int loop, int row, int col)
{
	auto pRef = new DoubleTapGrid();
	if(pRef && pRef->init(diff, loop, row, col))
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

bool DoubleTapGrid::init(int diff, int loop, int row, int col)
{
	if (!Node::init())
		return false;

	m_row = row;
	m_col = col;
	m_loop = loop;
	m_isRunning = false;
	m_touchesLabel = Label::create("0000", "Arial", 30);
	m_touchesLabel->setPosition(100, 400);
	this->addChild(m_touchesLabel);

	// 根据行、列，初始化一个空的二维容器
	m_zerglingGrid.resize(m_col);
	for (auto &vec : m_zerglingGrid)
		vec.resize(m_row);

	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			m_zerglingGrid[x][y] = createAZergling((Zergling::ZerglingColor)m_g[0][y][x], x, y);
		}
	}

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(DoubleTapGrid::onTouchesBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void DoubleTapGrid::setZerglingPixPos(Zergling* zergling, int x, int y)
{
	zergling->setPosition(x * GRID_WIDTH, y * GRID_WIDTH);
}

Zergling* DoubleTapGrid::createAZergling(Zergling::ZerglingColor color, int x, int y)
{
	Zergling * zergling = nullptr;
	if (color <= 0)
		return nullptr;
	zergling = Zergling::createByColor(color);
	
	setZerglingPixPos(zergling, x, y);
	addChild(zergling);

	return zergling;
}

void DoubleTapGrid::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* unused_event)
{
	// 如果倒计时还没有开始，则开始倒计时
	if (!m_isRunning)
	{
		m_isRunning = true;
		TimeManager::getInstance()->startCountDown();
	}
	
	int count = touches.size();
	m_touchesLabel->setString(StringUtils::format("%d", count));
	if(count == 2)		// 如果触摸点数为2
	{
		// log("touches count: %d", count);
		auto p1 = touches[0]->getLocation();
		auto p2 = touches[1]->getLocation();
		// 将坐标转化成格子坐标
		p1.x /= GRID_WIDTH;
		p1.y /= GRID_WIDTH;
		p2.y /= GRID_WIDTH;
		p2.y /= GRID_WIDTH;
		int x1 = (int)p1.x - 1;
		int y1 = (int)p1.y - 1;
		int x2 = (int)p2.x - 1;
		int y2 = (int)p2.y - 1;

		// 如果这两个被点击的位置都有狗
		if (m_zerglingGrid[x1][y1] && m_zerglingGrid[x2][y2])
		{
			// 如果两只狗的颜色相同
			if (m_zerglingGrid[x1][y1]->getColorType()
				== m_zerglingGrid[x2][y2]->getColorType())
			{
				log("crush!");
				// * add animation

				auto zergling1 = m_zerglingGrid[x1][y1];
				auto zergling2 = m_zerglingGrid[x2][y2];
				// 清空矩阵中的狗的指针
				m_zerglingGrid[p1.x][p1.y] = nullptr;
				m_zerglingGrid[p2.x][p2.y] = nullptr;
				// 将狗从矩阵的绘制节点中移除
				zergling1->tapped();
				zergling2->tapped();
			}
		}
	}
	else if(count == 1)
	{
		log("touches count: 1");
		auto p = touches[0]->getLocation();
		p.x /= GRID_WIDTH;
		p.y /= GRID_WIDTH;
		log("x = %f, y = %f", p.x, p.y);
		int x = (int)p.x - 1;
		int y = (int)p.y - 1;
		log("x = %d, y = %d", x, y);
		if (m_zerglingGrid[x][y])
		{
			log("color type: %d", m_zerglingGrid[x][y]->getColorType());
			auto zerg = m_zerglingGrid[x][y];
			m_zerglingGrid[x][y] = nullptr;
			zerg->tapped();
		}
		else
			log("none zergling.");
	}
}

void DoubleTapScene::newLevel(int diff)
{
	
}

void DoubleTapScene::update()
{
	
}