// CheckThethingScene.cpp
#include "CheckThethingScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include "TollgateControlLayer.h"
#include "Global.h"
#include "AnimationUtil.h"
#define MAX_UNIT_TYPE 10
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

bool CheckThethingScene::init(int diff, int loop)
{
	if (!Layer::init())
		return false;

	/*Sprite* sprite = Sprite::create("Res\zergling_big_1.png");
	auto size = Director::getInstance()->getVisibleSize();
	sprite->setPosition(size.height / 2, size.width / 2);
	this->addChild(sprite);*/

	//用矩阵中固定一个狗代替

	auto winSize = Director::getInstance()->getWinSize();

	auto UI = CSLoader::createNode("Tollgates/CheckTheThing.csb");
	addChild(UI);


	m_controlLayer = TollgateControlLayer::create();
	m_controlLayer->initTimeBar();
	m_controlLayer->scheduleUpdate();
	addChild(m_controlLayer);

	m_pauseBtn = (Button*)(UI->getChildByName("Button_pause"));
	m_timeBar = (LoadingBar*)(UI->getChildByName("LoadingBar_time"));
	m_timeText = (Text*)(UI->getChildByName("Text_time"));

	m_grid = CheckThethingGrid::create(diff, loop);
	m_grid->setPosition(0, 0);
	this->addChild(m_grid);

	return true;
}


cocos2d::Layer* CheckThethingScene::create(int diff, int loop)
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


void CheckThethingScene::newLevel(int diff)
{

}

void CheckThethingScene::update()
{

}

//根据困难和轮数创建矩阵数量
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

	// 根据行、列，初始化一个空的二维容器
	m_thingGrid.resize(m_col);
	for (auto &vec : m_thingGrid)
		vec.resize(m_row);
	m_sampleGrid.resize(m_col);

	generateNewThingGrid(m_diff);

/*	//这部分是对的，设置了三个不重复的标志
	int j, k, c;
	j = random(1, 2);
	k = random(3, 4);
	c = random(5, 6);
	m_thingGrid[0][1] = createUnit(j, 1, 0);
	m_thingGrid[0][2] = createUnit(k, 2, 0);
	m_thingGrid[0][3] = createUnit(c, 3, 0);


	int q;
	int w;
	int o;

	for (int n = 0; n <= 2; n++)
	{
		do
		{
			q = random(1, 3);
			w = random(1, 3);
			o = random(1, 6);
		} while (m_thingGrid[q][w]);
		//if ((q != 0 && w != 1) && (q != 0 && w != 2) && (q != 0 && w != 3))
		m_thingGrid[q][w] = createUnit(o, q, w);
	}*/

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CheckThethingGrid::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;

}

void CheckThethingGrid::setZerglingPixPos(farmerandflower* zergling, int x, int y)
{
	zergling->setPosition(x * width + l_margin, y * width + b_margin);
}

farmerandflower* CheckThethingGrid::createUnit(int type, int x, int y)
{
	farmerandflower * unit = nullptr;
	if (type <= 0)
		return nullptr;

	unit = farmerandflower::createByType(type);

	setZerglingPixPos(unit, x, y);
	unit->setScale(0.0);
	addChild(unit);
	auto big = ScaleTo::create(0.2, 1.0);
	unit->runAction(big);

	return unit;
}

//坐标获取，范围坐标与触屏坐标
cocos2d::Vec2 CheckThethingGrid::convertToGridPos(cocos2d::Vec2 pixPos)
{
	float x, y;
	x = (pixPos.x - l_margin) / width;
	y = (pixPos.y - b_margin) / width;
	return Vec2(x, y);
}

bool CheckThethingGrid::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	auto pos = touch->getLocation();
	for (int x = 0; x < m_col; x++)
		for (int y = 0; y < m_row; y++)
		{
			if (m_thingGrid[x][y] != nullptr && m_thingGrid[x][y]->getBoundingBox().containsPoint(pos)) 
			{
				int type = m_thingGrid[x][y]->getColorType();
				for (int k = 0; k < m_col; k++)
				{
					if (m_sampleGrid[k] != nullptr && type == m_sampleGrid[k]->getColorType())
					{
						// 如果找到可以消除的
						if (!m_isRunning)
						{
							m_isRunning = true;
							TimeManager::getInstance()->startCountDown();
						}

						PLAY_BURST_ANIMATION(m_sampleGrid[k]->getPosition(), 0.8f);
						m_sampleGrid[k]->removeFromParent();
						m_sampleGrid[k] = nullptr;
						PLAY_BURST_ANIMATION(m_thingGrid[x][y]->getPosition(), 0.8);
						m_thingGrid[x][y]->removeFromParent();
						m_thingGrid[x][y] = nullptr;
						
						// 如果被消光，但是loop>0
						if (getLivingSamplesNum() <= 0 && m_loop > 0)
						{
							generateNewThingGrid(0);
						}
						if(getLivingSamplesNum() <= 0 && m_loop <= 0)
						{
							_eventDispatcher->dispatchCustomEvent("tollgate_clear", (void*)"CheckTheUnit");
							CCLOG("CheckTheUnit clear");
						}
					}
				}
				return true;
			}
		}
	
	return true;
}

int CheckThethingGrid::getLivingSamplesNum()
{
	int count = 0;
	for (int x = 0; x < m_col; x++)
	{
		if (m_sampleGrid[x] != nullptr)
			count++;
	}

	return count;
}

void CheckThethingGrid::generateNewThingGrid(const int diff)
{
	for (int x = 0; x < m_col; x++)
		for (int y = 0; y < m_row; y++)
			if (m_thingGrid[x][y] != nullptr)
			{
				m_thingGrid[x][y]->removeFromParent();
				m_thingGrid[x][y] = nullptr;
			}
	for (int x = 0; x < m_col; x++)
		if (m_sampleGrid[x] != nullptr)
		{
			m_sampleGrid[x]->removeFromParent();
			m_sampleGrid[x] = nullptr;
		}

	m_loop--;
	int sum;
	int r, x, y;
	bool type[MAX_UNIT_TYPE + 1];		// 单位类型是否已经被创建
	for (int i = 0; i < MAX_UNIT_TYPE + 1; i++)
		type[i] = false;
	// 设置难度
	if (diff == 0)
		sum = 1;
	else if (diff == 1)
		sum = 2;
	else if (diff == 2)
		sum = 3;
	// create sample units
	for (int i = 0; i < m_col; i++)
	{
		CCLOG("CREATE first");
		r = random(1, MAX_UNIT_TYPE);
		if (i == 0)
		{
			m_sampleGrid[i] = farmerandflower::createByType(r);
			m_sampleGrid[i]->setPosition(Vec2(380 + 100 * i, 400));
			addChild(m_sampleGrid[i]);
		}
		else if(i == 1)
		{
			while (r == m_sampleGrid[0]->getColorType())
				r = random(1, MAX_UNIT_TYPE);
			m_sampleGrid[i] = farmerandflower::createByType(r);
			m_sampleGrid[i]->setPosition(Vec2(380 + 100 * i, 400));
			addChild(m_sampleGrid[i]);
		}
		else
		{
			while (r == m_sampleGrid[0]->getColorType() || r == m_sampleGrid[1]->getColorType())
				r = random(1, MAX_UNIT_TYPE);
			m_sampleGrid[i] = farmerandflower::createByType(r);
			m_sampleGrid[i]->setPosition(Vec2(380 + 100 * i, 400));
			addChild(m_sampleGrid[i]);
		}
		// 创建对应可以消除的单位
		type[r] = true;
		do
		{
			x = random(0, m_col - 1);
			y = random(0, m_row - 1);
		} while (m_thingGrid[x][y] != nullptr);
		m_thingGrid[x][y] = createUnit(r, x, y);
		CCLOG("CREATE %d at %d, %d", r, x, y);
	}
	// create grid units
	CCLOG("CREATE then");
	while(sum--)
	{
		do
		{
			r = random(1, MAX_UNIT_TYPE);
		} while (type[r] == true);
		type[r] = true;
		
		do
		{
			x = random(0, m_col - 1);
			y = random(0, m_row - 1);
		} while (m_thingGrid[x][y] != nullptr);
		m_thingGrid[x][y] = createUnit(r, x, y);
		CCLOG("CREATE %d at %d, %d", r, x, y);
	}
}