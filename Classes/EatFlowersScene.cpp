//EacFlowersScnen.cpp
#include "EatFlowersScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include "Flower.h"
#include "TollgateControlLayer.h"

USING_NS_CC;

using namespace cocos2d;
using namespace std;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;


// multi touches test
static const Color3B* s_TouchColors[3] = {
	&Color3B::YELLOW,
	&Color3B::BLUE,
	&Color3B::RED,
};

class TouchPoint : public Node
{
public:
	TouchPoint(const Vec2 &touchPoint, const Color3B &touchColor)
	{
		m_point = touchPoint;
		DrawNode* drawNode = DrawNode::create();
		auto s = Director::getInstance()->getWinSize();
		Color4F color(touchColor.r / 255.0f, touchColor.g / 255.0f, touchColor.b / 255.0f, 1.0f);
		drawNode->drawLine(Vec2(0, touchPoint.y), Vec2(s.width, touchPoint.y), color);
		drawNode->drawLine(Vec2(touchPoint.x, 0), Vec2(touchPoint.x, s.height), color);
		drawNode->drawDot(touchPoint, 3, color);
		addChild(drawNode);
	}

	static TouchPoint* touchPointWithParent(Node* pParent, const Vec2 &touchPoint, const Color3B &touchColor)
	{
		auto pRet = new (std::nothrow) TouchPoint(touchPoint, touchColor);
		pRet->setContentSize(pParent->getContentSize());
		pRet->setAnchorPoint(Vec2(0.0f, 0.0f));
		pRet->autorelease();
		return pRet;
	}
	CC_SYNTHESIZE(Vec2, m_point, Pt);
};

static Map<int, TouchPoint*> s_map;



Scene* EatFlowersScene::createScene(int diff, int loop)
{
	auto scene = Scene::create();
	auto layer = EatFlowersScene::create(diff, loop);
	scene->addChild(layer);
	return scene;
}

bool EatFlowersScene::init(int diff, int loop)
{
	if (!Layer::init())
		return false;


	auto winSize = Director::getInstance()->getWinSize();

	auto UI = CSLoader::createNode("Tollgates/EatFlowersScene.csb");
	addChild(UI);


	m_controlLayer = TollgateControlLayer::create();
	m_controlLayer->initTimeBar();
	m_controlLayer->scheduleUpdate();
	addChild(m_controlLayer);

	//m_pauseBtn = (Button*)(UI->getChildByName("Button_pause"));
	//m_timeBar = (LoadingBar*)(UI->getChildByName("LoadingBar_time"));
	//m_timeText = (Text*)(UI->getChildByName("Text_time"));

	m_grid = EatFlowersGrid::create(diff, loop);
	m_grid->setPosition(0, 0);
	this->addChild(m_grid);

	return true;
}

//下面的Layer* create代码差不多，固定
Layer* EatFlowersScene::create(int diff, int loop)
{
	auto pRef = new EatFlowersScene();
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


//接下去两个虚函数
void EatFlowersScene::newLevel(int diff)
{

}

void EatFlowersScene::update()
{

}

//根据困难和轮数创建矩阵数量
EatFlowersGrid* EatFlowersGrid::create(int diff, int loop, int row, int col)
{
	auto pRef = new EatFlowersGrid();
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

bool EatFlowersGrid::init(int diff, int loop, int row, int col)
{
	if (!Layer::init())
		return false;
	/*
	int r = 0;
	int b = 0;
	r = random(0, 2);
	b = random(2, 5);
	*/

	m_row = row;
	m_col = col;
	m_loop = loop;
	m_diff = diff;
	m_isRunning = false;
	m_touchesLabel = Label::create("0000", "Arial", 30);
	m_touchesLabel->setPosition(100, 500);
	this->addChild(m_touchesLabel);

	// 根据行、列，初始化一个空的二维容器
	m_flowersesGrid.resize(m_col);
	for (auto &vec : m_flowersesGrid)
		vec.resize(m_row);

	
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			m_flowersesGrid[x][y] = createflower((Flower::FlowerColor)n_g[0][y][x], x, y);
		}
	}


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(EatFlowersGrid::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(EatFlowersGrid::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;

}

void EatFlowersGrid::setZerglingPixPos(Flower* zergling, int x, int y)
{
	zergling->setPosition(x * grid_WIDTH + left_MARGIN, y * grid_WIDTH + bottom_MARGIN);
}

Flower* EatFlowersGrid::createflower(Flower::FlowerColor color, int x, int y)
{
	Flower * flower = nullptr;
	if (color <= 0)
		return nullptr;
	flower = Flower::createByColor(color);

	setZerglingPixPos(flower, x, y);
	addChild(flower);

	return flower;
}


void EatFlowersGrid::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

//坐标获取，范围坐标与触屏坐标
cocos2d::Vec2 EatFlowersGrid::convertToGridPos(cocos2d::Vec2 pixPos)
{
	float x, y;
	x = (pixPos.x - left_MARGIN) / grid_WIDTH;
	y = (pixPos.y - bottom_MARGIN) / grid_WIDTH;
	return Vec2(x, y);
}

bool EatFlowersGrid::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	if (!m_isRunning)
	{
		m_isRunning = true;
		TimeManager::getInstance()->startCountDown();
	}

	int r = 0;
	int b = 0;
	r = random(0, 2);
	b = random(0, 5);

	auto pos = touch->getLocation();
	pos = convertToGridPos(pos);

	int x1 = (int)pos.x;
	int y1 = (int)pos.y;
	if ((0 <= x1 && x1 < 3) && (0 <= y1 && y1 < 6) && m_flowersesGrid[x1][y1] && (x1!= 3 && y1 != 1) )//中心的狗不能被消除
	{
		// 如果倒计时还没有开始，则开始倒计时
		if (!m_isRunning)
		{
			m_isRunning = true;
			TimeManager::getInstance()->startCountDown();
		}
		
		auto flower = m_flowersesGrid[x1][y1];
		log("farmer pos x = %f, y = %f", flower->getPosition().x, flower->getPosition().y);

		// 清空矩阵中的花的指针
		m_flowersesGrid[x1][y1] = nullptr;

		//m_loop--;

		//m_flowersesGrid[r][b] = createflower(Flower::BLUE, r, b);//按一个消失，会出来一个。就是说会出来三个

		
		/*
		if (m_loop > 0 && getLivingFlowersNum() > 0)
		{
			m_flowersesGrid[r][b] = createflower(Flower::BLUE, r, b);
		}
		
		if (getLivingFlowersNum() <= 0 && m_loop <= 0)
		{
			_eventDispatcher->dispatchCustomEvent("tollgate_clear", (void*)"EatFlowers");
			CCLOG("EatFlowers clear");
		}
		*/

		flower->tapped();

	}
	return true;
}

int EatFlowersGrid::getLivingFlowersNum()
{
	int count = 0;
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			if (m_flowersesGrid[x][y] != nullptr)
				count++;
		}
	}
	return count;
}












	



