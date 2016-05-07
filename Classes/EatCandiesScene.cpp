//EacCandiesScnen.cpp
#include "EatCandiesScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include "Flower.h"

USING_NS_CC;

/*
using namespace std;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

static const Color3B* s_TouchColors[3] = {
	&Color3B::YELLOW,
	&Color3B::BLUE,
	&Color3B::GREEN,
};

bool EatCandiesScene::init(int diff, int loop)
{
	if (!Layer::init())
		return false;

	auto winSize = Director::getInstance()->getWinSize();

	auto UI = CSLoader::createNode("Tollgates/EatCandiesScene.csb");
	addChild(UI);

	m_pauseBtn = (Button*)(UI->getChildByName("Button_pause"));
	m_timeBar = (LoadingBar*)(UI->getChildByName("LoadingBar_time"));
	m_timeText = (Text*)(UI->getChildByName("Text_time"));

	n_grid = EatCandiesGrid::create(diff, loop);
	n_grid->setPosition(0, 0);
	this->addChild(n_grid);

	return true;
}

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


Scene* EatCandiesScene::createScene(int diff, int loop)
{
	auto scene = Scene::create();
	auto layer = EatCandiesScene::create(diff, loop);
	scene->addChild(layer);
	return scene;
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

void EatCandiesGrid::setFlower(Flower* flower, int x, int y)
{
	flower->setPosition(x * grid_width +  left_margin, y * grid_width + bottom_margin);
}


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

	Sprite* sprite = Sprite::create("zergling_big_1.jpg");
	auto size = Director::getInstance()->getVisibleSize();
	sprite->setPosition(size.height / 2, size.width / 2);
	this->addChild(sprite);

	m_row = row;
	m_col = col;
	m_loop = loop;
	m_isRunning = false;
	

=======
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


Scene* EatCandiesScene::createScene(int diff, int loop)
{
	auto scene = Scene::create();
	auto layer = EatCandiesScene::create(diff, loop);
	scene->addChild(layer);
	return scene;
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

void EatCandiesGrid::setFlower(Flower* flower, int x, int y)
{
	flower->setPosition(x * grid_width +  left_margin, y * grid_width + bottom_margin);
}


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

	Sprite* sprite = Sprite::create("zergling_big_1.jpg");
	auto size = Director::getInstance()->getVisibleSize();
	sprite->setPosition(size.height / 2, size.width / 2);
	this->addChild(sprite);

	m_row = row;
	m_col = col;
	m_loop = loop;
	m_isRunning = false;
	

>>>>>>> a8bf9fd8ec3ad10b573d29659c621a7fbdb16601
	m_flowerGrid.resize(m_col);
	for (auto &vec : m_flowerGrid)
		vec.resize(m_row);

	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			m_flowerGrid[x][y] = createFlower((Flower::FlowerColor)m_f[0][y][x], x, y);
		}
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(EatCandiesGrid::onTouchBegan, this);
		

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool EatCandiesGrid::onTouchBegan(Touch * touch, Event * unused_event)
{
	//Vec2 pos = touch->getLocation();
	//log("x = %f, y = %f", pos.x, pos.y);
	
}

Flower* EatCandiesGrid::createFlower(Flower::FlowerColor color, int x, int y)
{
	Flower * flower = nullptr;
	if (color <= 0)
		return nullptr;
	flower = Flower::createByColor(color);

	setFlower(flower, x, y);
	addChild(flower);

	return flower;

}

cocos2d::Vec2 EatCandiesGrid::convertToGridPos(cocos2d::Vec2 pixPos)
{
	float x, y;
	x = (pixPos.x - left_margin) / grid_width;
	y = (pixPos.y - bottom_margin) / grid_width;
	return Vec2(x, y);
}
*/
using namespace std;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;


// multi touches test
static const Color3B* s_TouchColors[5] = {
	&Color3B::YELLOW,
	&Color3B::BLUE,
	&Color3B::GREEN,
	&Color3B::RED,
	&Color3B::MAGENTA
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

	/*Sprite* sprite = Sprite::create("Res\zergling_big_1.png");
	auto size = Director::getInstance()->getVisibleSize();
	sprite->setPosition(size.height / 2, size.width / 2);
	this->addChild(sprite);*/

	//用矩阵中固定一个狗代替

	auto winSize = Director::getInstance()->getWinSize();

	auto UI = CSLoader::createNode("Tollgates/DoubleTapScene.csb");
	addChild(UI);

	m_pauseBtn = (Button*)(UI->getChildByName("Button_pause"));
	m_timeBar = (LoadingBar*)(UI->getChildByName("LoadingBar_time"));
	m_timeText = (Text*)(UI->getChildByName("Text_time"));

	m_grid = EatCandiesGrid::create(diff, loop);
	m_grid->setPosition(0, 0);
	this->addChild(m_grid);

	return true;
}

//下面的Layer* create代码差不多，固定
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


//接下去两个虚函数
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
	listener->onTouchBegan = CC_CALLBACK_2(EatCandiesGrid::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(EatCandiesGrid::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;

}

void EatCandiesGrid::setZerglingPixPos(Flower* zergling, int x, int y)
{
	zergling->setPosition(x * grid_WIDTH + left_MARGIN, y * grid_WIDTH + bottom_MARGIN);
}

Flower* EatCandiesGrid::createflower(Flower::FlowerColor color, int x, int y)
{
	Flower * flower = nullptr;
	if (color <= 0)
		return nullptr;
	flower = Flower::createByColor(color);

	setZerglingPixPos(flower, x, y);
	addChild(flower);

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
	if (!m_isRunning)
	{
		m_isRunning = true;
		TimeManager::getInstance()->startCountDown();
	}

	int r = 0;
	int b = 0;
	r = random(0, 2);
	b = random(2, 5);
	auto pos = touch->getLocation();
	pos = convertToGridPos(pos);

	int x1 = (int)pos.x;
	int y1 = (int)pos.y;
	if ((0 <= x1 && x1 < 10) && (0 <= y1 && y1 < 6) && m_flowersesGrid[x1][y1] && (x1!= 3 && y1 != 1) )//中心的狗不能被消除
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

		m_flowersesGrid[r][b] = createflower(Flower::BLUE, r, b);

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
			if (m_flowersesGrid[x][y] != nullptr)
				count++;
		}
	}
	return count;
}












	



