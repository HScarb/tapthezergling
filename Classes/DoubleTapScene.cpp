// DoubleTapScene.cpp
#include "DoubleTapScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include "Zergling.h"

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
	
	auto UI = CSLoader::createNode("Tollgates/DoubleTapScene.csb");
	addChild(UI);

	m_pauseBtn = (Button*)(UI->getChildByName("Button_pause"));
	m_timeBar = (LoadingBar*)(UI->getChildByName("LoadingBar_time"));
	m_timeText = (Text*)(UI->getChildByName("Text_time"));
	
	m_grid = DoubleTapGrid::create(diff, loop);
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

	// 根据行、列，初始化一个空的二维容器
	m_zerglingGrid.resize(m_row);
	for (auto &vec : m_zerglingGrid)
		vec.resize(m_col);

	for (int x = 0; x < m_col;x++)
	{
		for (int y = 0; y < m_row;y++)
		{
			auto s = Sprite::create("Res/zergling/SCs_Zergling_C3_02.png");
			m_zerglingGrid[x][y] = (Zergling*)Sprite::create("Res/zergling/SCs_Zergling_C3_02.png");
			this->addChild(m_zerglingGrid[x][y]);
		}
	}

	return true;
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
	if(count >= 2)
	{
		for(auto &item: touches)
		{
			auto touch = item;
			auto location = touch->getLocation();

		}
	}
}

void DoubleTapScene::newLevel(int diff)
{
	
}

void DoubleTapScene::update()
{
	
}