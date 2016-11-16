//EacCandiesScnen.cpp
#include "EatCandiesScene.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include "Flower.h"
#include "TollgateControlLayer.h"
#include "Global.h"

USING_NS_CC;

using namespace std;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace CocosDenshion;


Scene* EatCandiesScene::createScene(int diff, int loop)
{
	auto scene = Scene::create();
	auto layer = EatCandiesScene::create(diff, loop);
	scene->addChild(layer);
	return scene;
}

bool EatCandiesScene::init(int diff, int loop)
{
	if (!Layer::init())
		return false;

	auto winSize = Director::getInstance()->getWinSize();

	auto UI = CSLoader::createNode("Tollgates/EatCandiesScene.csb");
	addChild(UI);


	m_controlLayer = TollgateControlLayer::create();
	m_controlLayer->initTimeBar();
	m_controlLayer->scheduleUpdate();
	addChild(m_controlLayer, ZORDER_TOLLGATECONTROLLAYER);

	m_pauseBtn = (Button*)(UI->getChildByName("Button_pause"));
	m_timeBar = (LoadingBar*)(UI->getChildByName("LoadingBar_time"));
	m_timeText = (Text*)(UI->getChildByName("Text_time"));

	m_grid = EatCandiesGrid::create(diff, loop);
	m_grid->setPosition(0, 0);
	this->addChild(m_grid);


	return true;
}


cocos2d::Layer* EatCandiesScene::create(int diff, int loop)
{
	auto pRef = new EatCandiesScene();
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


void EatCandiesScene::newLevel(int diff)
{

}

void EatCandiesScene::update()
{

}

//根据困难和轮数创建矩阵数量
EatCandiesGrid* EatCandiesGrid::create(int diff, int loop, int row, int col)
{
	auto pRef = new EatCandiesGrid();
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

bool EatCandiesGrid::init(int diff, int loop, int row, int col)
{
	if (!Layer::init())
		return false;

	m_row = row;
	m_col = col;
	m_loop = loop;
	m_diff = diff;
	m_isRunning = false;

	// 根据行、列，初始化一个空的二维容器
	m_flowersesGrid.resize(m_col);
	for (auto &vec : m_flowersesGrid)
		vec.resize(m_row);


	int q;
	int w;
	int o;
	
	for (int n = 0; n <= 2; n++)
	{
		do
		{
			q = random(0, 5);
			w = random(0, 2);
			o = random(1, 3);
		} while (m_flowersesGrid[q][w]);
		m_flowersesGrid[q][w] = createflower(o, q, w);
	}
	

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(EatCandiesGrid::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(EatCandiesGrid::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;

}

void EatCandiesGrid::setZerglingPixPos(Flower* zergling, int x, int y)
{
	zergling->setPosition(x * grid_WIDTH + left_MARGIN, y * grid_WIDTH + bottom_MARGIN);
}

Flower* EatCandiesGrid::createflower(int color, int x, int y)
{
	Flower * flower = nullptr;
	if (color <= 0)
		return nullptr;

	flower = Flower::createByColor(color);

	setZerglingPixPos(flower, x, y);
	flower->setScale(0.0);
	addChild(flower);
	auto big = ScaleTo::create(0.2, 1.0);
	flower->runAction(big);

	return flower;
}


void EatCandiesGrid::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}


//坐标获取，范围坐标与触屏坐标
cocos2d::Vec2 EatCandiesGrid::convertToGridPos(cocos2d::Vec2 pixPos)
{
	float x, y;
	x = (pixPos.x - left_MARGIN) / grid_WIDTH;
	y = (pixPos.y - bottom_MARGIN) / grid_WIDTH;
	return Vec2(x, y);
}

bool EatCandiesGrid::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	int n = 0;
	int r = 0;
	int b = 0;
	r = random(0, 5);
	b = random(0, 2);
	n = random(1, 3);
	auto pos = touch->getLocation();
	pos = convertToGridPos(pos);

	int x1 = (int)pos.x;
	int y1 = (int)pos.y;
	if ((0 <= x1 && x1 < 6) && (0 <= y1 && y1 < 3) && m_flowersesGrid[x1][y1] )
	{
		// 如果倒计时还没有开始，则开始倒计时
		if (!m_isRunning)
		{
			m_isRunning = true;
			TimeManager::getInstance()->startCountDown();
		}
		// * add animation
		auto flower = m_flowersesGrid[x1][y1];
		log("farmer pos x = %f, y = %f", flower->getPosition().x, flower->getPosition().y);

		// 清空矩阵中的花的指针
		m_flowersesGrid[x1][y1] = nullptr;

		if (m_loop > 0 && getLivingFlowersNum() > 0)
		{
			if (m_flowersesGrid[r][b] == nullptr)
			{
				m_flowersesGrid[r][b] = createflower(n+1, r, b);
			}

			else if (m_flowersesGrid[r][b] != nullptr)
			{
				m_flowersesGrid[r + 1][b] = createflower(n, r + 1, b);
			}

			else if (m_flowersesGrid[r + 1][b] != nullptr)
			{
				m_flowersesGrid[r][b+1] = createflower(n+1, r , b+1);
			}

			else  if(m_flowersesGrid[r][b+1] != nullptr)
			{
				m_flowersesGrid[r+1][b+1] = createflower(n, r+1, b+1);
			}

			m_loop--;
		}

				

		if (getLivingFlowersNum() <= 0 && m_loop <= 0 )
		{
			_eventDispatcher->dispatchCustomEvent("tollgate_clear", (void*)"EatFlowers");
			CCLOG("EatFlowers clear");
	
		}

		flower->tapped();
	}
	return true;
}

int EatCandiesGrid::getLivingFlowersNum()
{
	int count = 0;
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			if (m_flowersesGrid[x][y] != nullptr )
				count++;
		}
	}

	return count;
}

void EatCandiesGrid::generateNewZerglingGrid(const int diff)
{
	m_loop--;
	int r = random(1, 4);
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			m_flowersesGrid[x][y] = createflower(r, x, y);
		}
	}
}