//FeedSnack.cpp
#include"FeedSnacks.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include"TollgateControlLayer.h"
#include "Global.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

Snack* Snack::create(SnackType type)
{
	auto bRet = new Snack();
	if (bRet && bRet->initWithType(type))
	{
		bRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(bRet);
	}
	return bRet;
}
bool Snack::initWithType(SnackType type)
{
	switch (type)
	{
	case NONE:
		return false;
	case SCV:
		this->initWithFile(PATH_SCV_SMALL);
		break;
	case Drone:
		this->initWithFile(PATH_DRONE_SMALL);
		break;
	case Probe:
		this->initWithFile(PATH_PROBE_SMALL);
		break;
	case FRED:
		this->initWithFile("Res/flower_1.png");
		break;
	case FYELLOW:
		this->initWithFile("Res/flower_2.png");
		break;
	case FBLUE:
		this->initWithFile("Res/flower_3.png");
		break;
	case RED:
		this->initWithFile("Res/zergling_small_0.png");
		this->setScale(0.5f);
		break;
	case ORANGE:
		this->initWithFile("Res/zergling_small_1.png");
		this->setScale(0.5f);
		break;
	case YELLOW:
		this->initWithFile("Res/zergling_small_2.png");
		this->setScale(0.5f);
		break;
	case GREEN:
		this->initWithFile("Res/zergling_small_3.png");
		this->setScale(0.5f);
		break;
	case CYAN:
		this->initWithFile("Res/zergling_small_4.png");
		this->setScale(0.5f);
		break;
	case BLUE:
		this->initWithFile("Res/zergling_small_5.png");
		this->setScale(0.5f);
		break;
	case PURPLE:
		this->initWithFile("Res/zergling_small_6.png");
		this->setScale(0.5f);
		break;
	default: break;
	}
	this->setAnchorPoint(Vec2(0, 0));// 设置锚点为左下角
	m_type = type;
	return true;
}

Scene* FeedSnacks::createScene(int diff, int loop)
{
	auto scene = Scene::create();
	auto layer = FeedSnacks::create(diff, loop);
	scene->addChild(layer);
	return scene;
}

bool FeedSnacks::init(int diff, int loop)
{
	if (!Layer::init())
		return false;
	auto winSize = Director::getInstance()->getWinSize();

	auto UI = CSLoader::createNode("Tollgates/FeedSnacks.csb");
	addChild(UI);

	m_controlLayer = TollgateControlLayer::create();
	m_controlLayer->initTimeBar();
	m_controlLayer->scheduleUpdate();
	addChild(m_controlLayer);

	m_grid = FeedSnacksGrid::create(diff, loop);
	m_grid->setPosition(0, 0);
	this->addChild(m_grid);
	return true;
}

Layer *FeedSnacks::create(int diff, int loop)
{
	auto pRef = new FeedSnacks();
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
void FeedSnacks::update()
{

}

/*
Feed Snacks Grid
*/

FeedSnacksGrid* FeedSnacksGrid::create(int diff, int loop, int row, int col)
{
	auto pRef = new FeedSnacksGrid();
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

bool FeedSnacksGrid::init(int diff, int loop, int row, int col)
{
	if (!Layer::init())
		return false;
	m_row = row;
	m_col = col;
	m_loop = loop;
	m_diff = diff;
	//m_isRunning = false;
	//根据行列初始化一个空的二维容器
	m_snackVector.resize(m_col);
	for (auto &vec : m_snackVector)
		vec.resize(m_col);

	//根据难度来创建关卡内容
	generateNewSnacksGrid(m_diff);
	//创建要消除的对象
	m_SnacktempBase = createATSnack();

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(FeedSnacksGrid::onTouchesBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}
cocos2d::Vec2 FeedSnacksGrid::convertToGridPos(cocos2d::Vec2 pixPos)
{
	float x, y;
	x = (pixPos.x - LEFT_MARGIn) / GRID_WIDTh;
	y = (pixPos.y - BOTTOM_MARGIn) / GRID_WIDTh;
	if (x < 0.0)
		x = -1.0;
	if (y < 0.0)
		y = -1.0;
	return Vec2(x, y);
}

void FeedSnacksGrid::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* unused_event)
{
	for (auto &item : touches)
	{
		auto touch = item;
		auto location = touch->getLocation();
		location = convertToGridPos(location);
		int x1 = (int)location.x;
		int y1 = (int)location.y;
		log("x1=%d,y1=%d", x1, y1);
		if ((0 <= x1 && x1 < 6) && (0 <= y1 && y1 < 3) && m_snackVector[x1][y1] && (m_snackVector[x1][y1]->getType() == m_temp))
		{
			// 如果倒计时还没有开始，则开始倒计时
			if (!m_isRunning)
			{
				m_isRunning = true;
				TimeManager::getInstance()->startCountDown();
			}
			// * add animation
			auto snack = m_snackVector[x1][y1];
			// 清空矩阵中的狗的指针
			m_snackVector[x1][y1] = nullptr;
			// 将狗从矩阵的绘制节点中移除
			snack->removeFromParent();
			if (getLivingAtypeSnackNum() == 0)
			{
				m_SnacktempBase->removeFromParent();
				if (getLivingAllSnackNum() != 0)
				{
					m_SnacktempBase = createATSnack();
				}
				else if (getLivingAllSnackNum() == 0 && m_loop > 0)
				{
					generateNewSnacksGrid(0);
					m_SnacktempBase = createATSnack();
				}
				else if (getLivingAllSnackNum() <= 0 && m_loop <= 0)
				{
					_eventDispatcher->dispatchCustomEvent("tollgate_clear", (void*)"FeedSnacks");
					CCLOG("FeedSnacks clear");
				}
			}

		}
	}
}


void FeedSnacksGrid::generateNewSnacksGrid(const int diff)
{
	m_loop--;
	int sum = 0;
	if (m_diff == 0)
	{
		sum = 6;
	}
	else if (m_diff == 1)
	{
		sum = 8;
	}
	else if (m_diff == 2)
	{
		sum = 10;
	}
	int t = random(1, 6);
	Snack::SnackType type = ((Snack::SnackType)t);
	m_Type = type;
	for (int i = 1; i <= sum; i++)
	{
		int x = random(0, 5);
		int y = random(0, 2);
		for (; (m_snackVector[x][y] != nullptr) || (x == 2 && y == 1) || (x == 3 && y == 1) || (x == 2 && y == 2) || (x == 3 && y == 2);)
		{
			x = random(0, 5);
			y = random(0, 2);
		}
		Snack * temp=0;
		if (type >= 1 && type <= 3)
		{
			temp = Snack::create((Snack::SnackType)random(1, 3));
		}
		else if (type >= 4 && type <= 6)
		{
			temp = Snack::create((Snack::SnackType)random(4, 6));
		}
		else if (type >= 7 && type <= 13)
		{
			temp = Snack::create((Snack::SnackType)random(7, 13));
		}
		SetSnackPixPos(temp, x, y);
		this->addChild(temp);
		m_snackVector[x][y] = temp;
	}
	
}

Snack * FeedSnacksGrid::createATSnack()
{
	Snack * temp;
	Snack::SnackType type = (Snack::SnackType)0;
	if (m_Type >= 1 && m_Type <= 3)
	{
		type = (Snack::SnackType)random(1, 3);
	}
	else if (m_Type >= 4 && m_Type <= 6)
	{
		type = (Snack::SnackType)random(4, 6);
	}
	else if (m_Type >= 7 && m_Type <= 13)
	{
		type = (Snack::SnackType)random(7, 13);
	}
	m_temp = type;
	temp = Snack::create(type);
	temp->setPosition(530, 400);
	temp->setScale(0.0);
	cocos2d::ScaleTo *big;
	if (m_temp >= 7 && m_temp <= 13)
	{
		big = ScaleTo::create(0.35, 0.5);
	}
	else
		big = ScaleTo::create(0.35, 1.0);
	this->addChild(temp, 3);
	temp->runAction(big);
	if (getLivingAtypeSnackNum() == 0)
	{

		temp->removeFromParent();
		temp = createATSnack();
	}
	return temp;
}

void FeedSnacksGrid::SetSnackPixPos(Snack* snack, int x, int y)
{
	snack->setPosition(x* GRID_WIDTh + LEFT_MARGIn + 25, y*GRID_WIDTh + BOTTOM_MARGIn + 25);
}

int FeedSnacksGrid::getLivingAtypeSnackNum()
{
	int count = 0;
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			if (m_snackVector[x][y] != nullptr)
			{
				if (m_snackVector[x][y]->getType() == m_temp)
					count++;
			}
		}
	}
	return count;
}

int FeedSnacksGrid::getLivingAllSnackNum()
{
	int count = 0;
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			if (m_snackVector[x][y] != nullptr)
			{
				count++;
			}
		}
	}
	return count;
}
