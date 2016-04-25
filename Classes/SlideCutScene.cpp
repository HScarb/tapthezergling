//SlideScene
#include"SlideCutScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace cocos2d;

/*class TouchPoint : public Node
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
static Map<int, TouchPoint*> s_map;*/

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
	m_grid = SlideCutGrid::create(diff, loop);
	m_grid->setPosition(0, 0);
	this->addChild(m_grid);
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
	m_famrerGrid.resize(m_col);
	for (auto &vec : m_famrerGrid)
		vec.resize(m_row);

	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			m_famrerGrid[x][y] = createAFarmer((Farmer::Farmerappear)m_a[0][y][x], x, y);
		}
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event *event){};
	listener->onTouchMoved = [](Touch* touch, Event *event)
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
		if ((0 <= x1 && x1 <8 ) && (0 <= y1 && y1 < 6)&&m_famrerGrid[x1][y1])
		{
			log("crush!");
			// * add animation
			auto zergling1 = m_farmerGrid[x1][y1];
			// 清空矩阵中的狗的指针
			m_farmerGrid[x1][y1] = nullptr;
			// 将狗从矩阵的绘制节点中移除
			zergling1->tapped();
		}

	};
	listener->onTouchEnded = [=](Touch* touch, Event *event){

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}
void SlideCutGrid::setFarmerPixPos(Farmer* farmer, int x, int y)
{
	farmer->setPosition(x * Grid_WIDTH + Left_MARGIN, y * Grid_WIDTH + Bottom_MARGIN);
}

Farmer* SlideCutGrid::createAFarmer(Farmer::Farmerappear appear , int x, int y)
{
	Farmer * farmer = nullptr;
	if (appear <= 0)
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