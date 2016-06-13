//CheckThething.cpp
#include "CheckThethingScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include "TollgateControlLayer.h"
#include "farmerandflower.h"
#include <string.h>

USING_NS_CC;

using namespace std;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

Scene* CheckThethingScene::createScene(int diff, int loop)
{
	auto scene = Scene::create();
	auto layer = CheckThethingScene::create(diff, loop);
	scene->addChild(layer);
	return scene;

}

void CheckThethingScene::newLevel(int diff)
{
}

void CheckThethingScene::update()
{
}

Layer* CheckThethingScene::create(int diff, int loop)
{
	auto pRef = new CheckThethingScene();
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


bool CheckThethingScene::init(int diff, int loop)
{
	if (!Layer::init())
		return false;
	auto winSize = Director::getInstance()->getWinSize();

	auto UI = CSLoader::createNode("Tollgates/CheckTheThing.csb");
	addChild(UI);

	m_controlLayer = TollgateControlLayer::create();
	m_controlLayer->initTimeBar();
	m_controlLayer->scheduleUpdate();
	addChild(m_controlLayer);

	m_grid = CheckThethingGrid::create(diff, loop);
	m_grid->setPosition(0, 0);
	this->addChild(m_grid);

	return true;
}

int CheckThethingGrid::getLivingFarmersNum()
{
	int count = 0;
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			if (m_thingGrid[x][y] == m_farmerandflowerGrid[0])
				count++;
			if (m_thingGrid[x][y] == m_farmerandflowerGrid[1])
				count++;
			if (m_thingGrid[x][y] == m_farmerandflowerGrid[2])
				count++;
		}
	}
	return count;
}


/*
void CheckThethingGrid::generateNewFarmersGrid(const int diff)
{
	m_loop--;
	int r = random(1, 3);
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			if (c_g[0][y][x] != 0)
				m_farmerGrid[x][y] = createAFarmer(r, x, y);
		}
	}
	log("loop=%d", m_loop);
}
*/


cocos2d::Vec2 CheckThethingGrid::convertToGridPos(cocos2d::Vec2 pixPos)
{
	float x, y;

	x = (pixPos.x - l_margin) /width;
	y = (pixPos.y - b_margin) / width;
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

void CheckThethingGrid::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
}

CheckThethingGrid* CheckThethingGrid::create(int diff, int loop, int row, int col)
{
	auto pRef = new CheckThethingGrid();
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

bool CheckThethingGrid::init(int diff, int loop, int row, int col)
{
	if (!Layer::init())
		return false;

	m_row = row;
	m_col = col;
	m_loop = loop;
	m_diff = diff;
	m_isRunning = false;

	m_farmerandflowerGrid.resize(m_row);


	int o;
	int i;
	int l;
	o = random(1, 2);
	i = random(3, 4);
	l = random(5, 6);
	m_farmerandflowerGrid[1] = sampleAppear(o, 1);
	m_farmerandflowerGrid[2] = sampleAppear(i, 2);
	m_farmerandflowerGrid[3] = sampleAppear(l, 3);
	
	
	m_thingGrid.resize(m_col);
	for (auto &vec : m_thingGrid)
		vec.resize(m_row);

	int j;
	int k;
	int c;
	for (int n = 0; n <= 2; n++)
	{
		do
		{
			j = random(0, 2);
			k = random(0, 2);
			c = random(1, 6);
		} while (m_thingGrid[j][k]);
		m_thingGrid[j][k] = farmerandflowerAppear(c, j, k);
	}
	
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = CC_CALLBACK_2(CheckThethingGrid::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(CheckThethingGrid::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}

void CheckThethingGrid::setFarmerPixPos(Farmerandflower* farmerandflower, int x, int y)
{
	farmerandflower->setPosition(x * width + l_margin, y * width + b_margin);
}

void CheckThethingGrid::setSamplePixPos(Farmerandflower* farmerandflower, int y)
{
	farmerandflower->setPosition(200, y * width + b_margin);
}

Farmerandflower* CheckThethingGrid::sampleAppear(int type, int y)
{
	Farmerandflower * farmerandflower = nullptr;
	if (type == 0)
		return nullptr;
	farmerandflower = Farmerandflower::farmerandflowerAppear(type);
	setSamplePixPos(farmerandflower, y);
	addChild(farmerandflower);
}

Farmerandflower* CheckThethingGrid::farmerandflowerAppear(int color, int x, int y)
{
	Farmerandflower * farmerandflower = nullptr;
	if (color == 0)
		return nullptr;
	farmerandflower = Farmerandflower::farmerandflowerAppear(color);
	setFarmerPixPos(farmerandflower, x, y);
	addChild(farmerandflower);
}

bool CheckThethingGrid::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
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


	if ((0 <= x1 && x1 < 3) && (0 <= y1 && y1 < 3) && m_thingGrid[x1][y1])
	{

		if (
			(m_thingGrid[x1][y1] == m_farmerandflowerGrid[0]) ||
			(m_thingGrid[x1][y1] == m_farmerandflowerGrid[1]) ||
			(m_thingGrid[x1][y1] == m_farmerandflowerGrid[2])
			)
		{
			// 如果倒计时还没有开始，则开始倒计时
			if (!m_isRunning)
			{
				m_isRunning = true;
				TimeManager::getInstance()->startCountDown();
			}

			auto farmerandflower = m_thingGrid[x1][y1];
			//log("farmer pos x = %f, y = %f", flower->getPosition().x, flower->getPosition().y);
			farmerandflower->tapped();
			m_thingGrid[x1][y1] = nullptr;

			//flower->tapped();

			if (getLivingFarmersNum() <= 0 && m_loop <= 0)
			{
				_eventDispatcher->dispatchCustomEvent("tollgate_clear", (void*)"EatFlowers");
				CCLOG("EatFlowers clear");
			}
		}
	}
	return true;

}