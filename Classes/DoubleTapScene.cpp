// DoubleTapScene.cpp
#include "DoubleTapScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include "TollgateControlLayer.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

// multi touches test
static const Color3B* s_TouchColors[3] = {
	&Color3B::YELLOW,
	&Color3B::BLUE,
	&Color3B::GREEN,
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

	m_controlLayer = TollgateControlLayer::create();		// �����ؿ����Ʋ�
	m_controlLayer->initTimeBar();			// ��ʼ��ʱ����
	m_controlLayer->scheduleUpdate();		// ��ʼˢ��
	addChild(m_controlLayer);
	
	m_grid = DoubleTapGrid::create(diff, loop);
	m_grid->setPosition(0, 0);
	this->addChild(m_grid);

	// add custom event listener
//	auto clearListener = EventListenerCustom::create("tollgate_clear", CC_CALLBACK_1(DoubleTapScene::tollgateClear, this));
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(clearListener,this);

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

void DoubleTapScene::newLevel(int diff)
{

}

void DoubleTapScene::update()
{

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
	if (!Layer::init())
		return false;

	m_row = row;
	m_col = col;
	m_loop = loop;
	m_diff = diff;
	m_isRunning = false;

	// �����С��У���ʼ��һ���յĶ�ά����
	m_zerglingGrid.resize(m_col);
	for (auto &vec : m_zerglingGrid)
		vec.resize(m_row);

	generateNewZerglingGrid(m_diff);

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(DoubleTapGrid::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(DoubleTapGrid::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(DoubleTapGrid::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void DoubleTapGrid::setZerglingPixPos(Zergling* zergling, int x, int y)
{
	zergling->setPosition(x * GRID_WIDTH + LEFT_MARGIN, y * GRID_WIDTH + BOTTOM_MARGIN);
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
/*
	for (auto &item : touches)
	{
		auto touch = item;
		auto location = touch->getLocation();
		auto touchPoint = TouchPoint::touchPointWithParent(this, location, *s_TouchColors[touch->getID() % 5]);

		addChild(touchPoint);
		s_map.insert(touch->getID(), touchPoint);
	}
*/
	if(s_map.size() == 2)
	{
		// log("touches count: %d", count);
		Vec2 p[2];
		int c = 0;
		vector<int> keys;
		keys = s_map.keys();
		for(auto key : keys)
		{
			p[c] = (s_map.at(key))->getPt();
			// ������ת���ɸ�������
			p[c] = convertToGridPos(p[c]);
			c++;
		}
		int x1 = (int)p[0].x;
		int y1 = (int)p[0].y;
		int x2 = (int)p[1].x;
		int y2 = (int)p[1].y;
		// ����������������λ�ö��ھ��������й�
		if ((0 <= x1 && x1 < 6) && (0 <= y1 && y1 < 3) 
			&& (0 <= x2 && x2 < 6) && (0 <= y2 && y2 < 3) 
			&& m_zerglingGrid[x1][y1] && m_zerglingGrid[x2][y2])
		{
			// �����ֻ������ɫ��ͬ
			if (m_zerglingGrid[x1][y1]->getColorType()
				== m_zerglingGrid[x2][y2]->getColorType())
			{
				log("crush!");
				// �������ʱ��û�п�ʼ����ʼ����ʱ
				if (!m_isRunning)
				{
					m_isRunning = true;
					TimeManager::getInstance()->startCountDown();
				}
				// * add animation
				auto zergling1 = m_zerglingGrid[x1][y1];
				auto zergling2 = m_zerglingGrid[x2][y2];
				// ��վ����еĹ���ָ��
				m_zerglingGrid[x1][y1] = nullptr;
				m_zerglingGrid[x2][y2] = nullptr;
				// �����Ӿ���Ļ��ƽڵ����Ƴ�
				zergling1->tapped();
				zergling2->tapped();

				// ����������⣬����loop>0
				if(getLivingZerglingsNum() == 0 && m_loop > 0)
				{
					generateNewZerglingGrid(m_diff);
				}
				// ����������⣬����loop<=0,�ؿ����
				else if(getLivingZerglingsNum() == 0 && m_loop <= 0)
				{
					_eventDispatcher->dispatchCustomEvent("tollgate_clear", (void*)"DoubleTap");
					CCLOG("DoubleTap clear");
				}
			}
		}
	}
	/*else if (s_map.size() == 1)
	{
		Vec2 p;
		vector<int> keys;
		keys = s_map.keys();
		for (auto key : keys)
		{
			p = (s_map.at(key))->getPt();
			p = convertToGridPos(p);
		}
		log("touches count: 1");
		int x = (int)p.x;
		int y = (int)p.y;
		log("x = %d, y = %d", x, y);
		if ((0 <= x && x < 6) && (0 <= y && y < 3) && m_zerglingGrid[x][y])
		{
			log("color type: %d", m_zerglingGrid[x][y]->getColorType());
			m_touchesLabel->setString(StringUtils::format("Color Type: %d", m_zerglingGrid[x][y]->getColorType()));
			auto zerg = m_zerglingGrid[x][y];
			m_zerglingGrid[x][y] = nullptr;
			zerg->tapped();
		}
		else
			log("none zergling.");
	}*/
}

void DoubleTapGrid::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* unused_event)
{
/*	int count = 0;
	if (count == 2)		// �����������Ϊ2
	{
		// log("touches count: %d", count);
		auto p1 = touches[0]->getLocation();
		auto p2 = touches[1]->getLocation();
		// ������ת���ɸ�������
		p1.x /= GRID_WIDTH;
		p1.y /= GRID_WIDTH;
		p2.y /= GRID_WIDTH;
		p2.y /= GRID_WIDTH;
		int x1 = (int)p1.x - 1;
		int y1 = (int)p1.y - 1;
		int x2 = (int)p2.x - 1;
		int y2 = (int)p2.y - 1;

		// ����������������λ�ö��й�
		if (m_zerglingGrid[x1][y1] && m_zerglingGrid[x2][y2])
		{
			// �����ֻ������ɫ��ͬ
			if (m_zerglingGrid[x1][y1]->getColorType()
				== m_zerglingGrid[x2][y2]->getColorType())
			{
				log("crush!");
				// * add animation

				auto zergling1 = m_zerglingGrid[x1][y1];
				auto zergling2 = m_zerglingGrid[x2][y2];
				// ��վ����еĹ���ָ��
				m_zerglingGrid[p1.x][p1.y] = nullptr;
				m_zerglingGrid[p2.x][p2.y] = nullptr;
				// �����Ӿ���Ļ��ƽڵ����Ƴ�
				zergling1->tapped();
				zergling2->tapped();
			}
		}
	}
	else if (count == 1)
	{
/*		log("touches count: 1");
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
			log("none zergling.");#1#
	}*/
}

void DoubleTapGrid::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* unused_event)
{
	for (auto &item : touches)
	{
		auto touch = item;
		auto pTP = s_map.at(touch->getID());
		removeChild(pTP, true);
		s_map.erase(touch->getID());
	}
}

cocos2d::Vec2 DoubleTapGrid::convertToGridPos(cocos2d::Vec2 pixPos)
{
	float x, y;
	x = (pixPos.x - LEFT_MARGIN) / GRID_WIDTH;
	y = (pixPos.y - BOTTOM_MARGIN) / GRID_WIDTH;
	if (x < 0.0)
		x = -1.0;
	if (y < 0.0)
		y = -1.0;
	return Vec2(x, y);
}

void DoubleTapGrid::generateNewZerglingGrid(const int diff)
{
	m_loop--;
	int index = random(0, 5 * (diff + 1) - 1);
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			m_zerglingGrid[x][y] = createAZergling((Zergling::ZerglingColor)m_g[index][y][x], x, y);
		}
	}
}

int DoubleTapGrid::getLivingZerglingsNum()
{
	int count = 0;
	for (int x = 0; x < m_col;x++)
	{
		for (int y = 0; y < m_row;y++)
		{
			if (m_zerglingGrid[x][y] != nullptr)
				count++;
		}
	}
	return count;
}