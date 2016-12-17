//fitthecircle.cpp
#include "fitthecircle.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include "GlobalConst.h"
#include "FilterSprite.h"
#include "TollgateControlLayer.h"
#include "Circle.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace CocosDenshion;

int i = random(0, 3);   //全局变量，表示目标花的旋转角度，0=0°，1=90°，2=180°，3=270°
int o = random(0, 3);
int p = random(0, 3);
int q = random(0, 3);
int d = 0;
int a = 0;
int b = 0;
int c = 0;
int a1, a2, a3, a4;
int ag1, ag2, ag3, ag4; //四个角度值

Scene* fitthecircleScene::createScene(int diff, int loop)
{
	auto scene = Scene::create();
	auto layer = fitthecircleScene::create(diff, loop);
	scene->addChild(layer);
	return scene;
}

cocos2d::Layer* fitthecircleScene::create(int diff, int loop)
{
	auto pRef = new fitthecircleScene();
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

bool fitthecircleScene::init(int diff, int loop)
{
	if (!Layer::init())
		return false;

	auto UI = CSLoader::createNode("Tollgates/fitthecircle.csb");
	addChild(UI);

	a = 0;b = 0;c = 0;d = 0;
	a1 = 0; a2 = 0; a3 = 0; a4 = 0;

	m_controlLayer = TollgateControlLayer::create();
	m_controlLayer->initTimeBar();
	m_controlLayer->scheduleUpdate();
	addChild(m_controlLayer, ZORDER_TOLLGATECONTROLLAYER);

	m_pauseBtn = (Button*)(UI->getChildByName("Button_pause"));
	m_timeBar = (LoadingBar*)(UI->getChildByName("LoadingBar_time"));
	m_timeText = (Text*)(UI->getChildByName("Text_time"));

	m_grid = fitthecircleGrid::create(diff, loop);
	m_grid->setPosition(0, 0);
	this->addChild(m_grid);

	return true;
}

int fitthecircleGrid::getCircle()
{
	int count = 0;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			if (m_spriteGrid[x][y] != nullptr )
				count++;
		}
	}

	return count;
}

Circle* fitthecircleGrid::createCircle(Circle::CircleType color, int x, int y)
{
	Circle * circle = nullptr;
	if (color <= 0)
		return nullptr;
	circle = Circle::createByColor(color);

	setCirclePixPos(circle, x, y);
	addChild(circle);

	return circle;
}

void fitthecircleGrid::setCirclePixPos(Circle* circle, int x, int y)
{
	circle->setPosition(x * WIDTH + L_MARGIN, y * WIDTH + B_MARGIN);
}

fitthecircleGrid* fitthecircleGrid::create(int diff, int loop, int row, int col)
{
	auto pRef = new fitthecircleGrid();
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

bool fitthecircleGrid::init(int diff, int loop,int row,int col)
{
	m_row = row;
	m_col = col;
	m_loop = loop;
	m_diff = diff;
	m_isRunning = false;

	// 根据行、列，初始化一个空的二维容器，这个容器是3*6的大小
	m_spriteGrid.resize(m_col);
	for (auto &vec : m_spriteGrid)
		vec.resize(m_row);

	generateGrid(m_diff);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(fitthecircleScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(fitthecircleScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

//每完成一个圈，所有剩余的圈旋转速度+1
void fitthecircleScene::speedup()
{
	GameManager::getInstance()->setspeed(GameManager::getInstance()->getspeed() + 1);
}

void fitthecircleGrid::generateGrid(const int diff)
{
	m_loop--;
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			m_spriteGrid[x][y] = createCircle((Circle::CircleType)j_g[0][y][x], x, y);
		}
	}
}

cocos2d::Vec2 fitthecircleGrid::convertToGridPos(cocos2d::Vec2 pixPos)
{
	float x, y;
	x = (pixPos.x - L_MARGIN) / WIDTH;
	y = (pixPos.y - B_MARGIN) / WIDTH;

	return Vec2(x, y);
}

void fitthecircleGrid::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	return;
}

bool fitthecircleGrid::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	auto pos = touch->getLocation();
	for (int x = 0; x < m_col; x++)
	for (int y = 0; y < m_row; y++)
	{
		//判断是否初始化就已对准
		if (a == i){ m_spriteGrid[2][2] == nullptr; a1 = 1; }
		if (b == o){ m_spriteGrid[4][2] == nullptr; a2 = 1; }
		if (c == p){ m_spriteGrid[2][0] == nullptr; a3 = 1; }
		if (d == q){ m_spriteGrid[4][0] == nullptr; a4 = 1; }
		if (m_spriteGrid[x][y] != nullptr && m_spriteGrid[x][y]->getBoundingBox().containsPoint(pos)) //你点击的图标不是nullptr，而且图标被点击了
		{

			if (!m_isRunning)
			{
				m_isRunning = true;
				TimeManager::getInstance()->startCountDown();
			}

			int type = m_spriteGrid[x][y]->getColorType();    //获取得到的图标类型，一共有8种类型。5，6，7，8是旋转的图标
			if (type == 5)
			{
				if (a == i){ m_spriteGrid[x][y] = nullptr; a1 = 1; }
				if (a != i)
				{
					m_spriteGrid[x][y]->runAction(RotateBy::create(0.1, 90));
					a++;
					if (a == i){
						m_spriteGrid[x][y] = nullptr; a1 = 1;
					}
				}
			}
			if (type == 6)
			{
				if (b == o){ m_spriteGrid[x][y] = nullptr; a2 = 1; }
				if (b != o)
				{
					m_spriteGrid[x][y]->runAction(RotateBy::create(0.1, 90));
					b++;
					if (b == o){
						m_spriteGrid[x][y] = nullptr; a2 = 1;
					}
				}
			}
			if (type == 7)
			{
				if (c == p){ m_spriteGrid[x][y] = nullptr; a3 = 1; }
				if (c != p)
				{
					m_spriteGrid[x][y]->runAction(RotateBy::create(0.1, 90));
					c++;
					if (c == p){
						m_spriteGrid[x][y] = nullptr; a3 = 1;
					}
				}
			}
			if (type == 8)
			{
				if (d == q){ m_spriteGrid[x][y] = nullptr; a4 = 1; }
				if (d != q)
				{
					m_spriteGrid[x][y]->runAction(RotateBy::create(0.1, 90));
					d++;
					if (d == q){
						m_spriteGrid[x][y] = nullptr; a4 = 1;
					}
				}
			}
			if (a1 == 1 && a3 == 1 && a2 == 1 && a4 == 1)
			{
				_eventDispatcher->dispatchCustomEvent("tollgate_clear", (void*)"fitthecircle");
				CCLOG("fitthecircle clear");
			}
		}
	}
	return true;
}

bool Circle::init(int color)
{
	if (!FilterSprite::init())
		return false;

	m_colorType = color;

	switch (m_colorType)
	{
	case 1:
		this->initWithFile(StringUtils::format("Res/flower/flower_1.%d.png", i));
		break;
	case 2:
		this->initWithFile(StringUtils::format("Res/flower/flower_2.%d.png", o));
		break;
	case 3:
		this->initWithFile(StringUtils::format("Res/flower/flower_3.%d.png", p));
		break;
	case 4:
		this->initWithFile(StringUtils::format("Res/flower/flower_4.%d.png", q));
		break;
	case 5:
		this->initWithFile(StringUtils::format("Res/flower/flower_9.0.png"));
		this->runAction(ScaleTo::create(0, 1.5));
		break;
	case 6:
		this->initWithFile(StringUtils::format("Res/flower/flower_6.0.png"));
		this->runAction(ScaleTo::create(0, 1.5));
		break;
	case 7:
		this->initWithFile(StringUtils::format("Res/flower/flower_7.0.png"));
		this->runAction(ScaleTo::create(0, 1.5));
		break;
	case 8:
		this->initWithFile(StringUtils::format("Res/flower/flower_8.0.png"));
		this->runAction(ScaleTo::create(0, 1.5));
		break;
	default: break;
	}

	return true;
}
