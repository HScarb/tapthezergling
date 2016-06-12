
//EacCandiesScnen.cpp
#include "CheckThethingScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include "Flower.h"
#include "TollgateControlLayer.h"

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

	//�þ����й̶�һ��������

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

//�������Ѻ�����������������
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

	/*
	Sprite* sprite = Sprite::create("Res/smallzer.png");
	auto size = Director::getInstance()->getVisibleSize();
	sprite->setPosition(size.height / 2, size.width / 2);
	this->addChild(sprite);
	*/

	// �����С��У���ʼ��һ���յĶ�ά����
	m_thingGrid.resize(m_col);
	for (auto &vec : m_thingGrid)
		vec.resize(m_row);

	//generateNewZerglingGrid(m_diff);

	/*
	for (int x = 0; x < m_col; x++)
	{
	for (int y = 0; y < m_row; y++)
	{
	m_flowersesGrid[x][y] = createflower((Flower::FlowerColor)n_g[0][y][x], x, y);
	}
	}
	*/
	//�ⲿ���ǶԵģ��������������ظ��ı�־
	int j, k, c;
	j = random(1, 2);
	k = random(3, 4);
	c = random(5, 6);
	m_thingGrid[0][1] = createflower(j, 1, 0);
	m_thingGrid[0][2] = createflower(k, 2, 0);
	m_thingGrid[0][3] = createflower(c, 3, 0);


	int q;
	int w;
	int o;

	for (int n = 0; n <= 2; n++)
	{
		do
		{
			q = random(1, 5);
			w = random(0, 2);
			o = random(1, 6);
		} while (m_thingGrid[q][w]);
		m_thingGrid[q][w] = createflower(o, q, w);
	}


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CheckThethingGrid::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(CheckThethingGrid::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;

}

void CheckThethingGrid::setZerglingPixPos(farmerandflower* zergling, int x, int y)
{
	zergling->setPosition(x * width + l_margin, y * width + b_margin);
}

farmerandflower* CheckThethingGrid::createflower(int color, int x, int y)
{
	farmerandflower * farmerandflower = nullptr;
	if (color <= 0)
		return nullptr;

	farmerandflower = farmerandflower::createByColor(color);

	setZerglingPixPos(farmerandflower, x, y);
	addChild(farmerandflower);

	return farmerandflower;
}


void CheckThethingGrid::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}



/*cocos2d::Animate* EatCandiesGrid::createAnimate()
{
int iFrameNum = 4;
SpriteFrame* frame = NULL;
Vector<SpriteFrame*>frameVec;

for (int i = 1; i <= iFrameNum; i++)
{
frame = SpriteFrame::create(StringUtils::format("flower_1.%d.png", i), Rect(0, 0, 130, 130));
frameVec.pushBack((frame));
}

Animation* animation = Animation::createWithSpriteFrames(frameVec);
animation->setLoops(-1);
animation->setDelayPerUnit(0.1f);

Animate* action = Animate::create(animation);

return action;
}
*/



//�����ȡ����Χ�����봥������
cocos2d::Vec2 CheckThethingGrid::convertToGridPos(cocos2d::Vec2 pixPos)
{
	float x, y;
	x = (pixPos.x - l_margin) / width;
	y = (pixPos.y - b_margin) / width;
	return Vec2(x, y);
}

bool CheckThethingGrid::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	if (!m_isRunning)
	{
		m_isRunning = true;
		TimeManager::getInstance()->startCountDown();
	}

	int r = random(0, 4);
	int b = random(0, 1);
	int n = random(1, 6);
	auto pos = touch->getLocation();
	pos = convertToGridPos(pos);

	int x1 = (int)pos.x;
	int y1 = (int)pos.y;
	if ((0 <= x1 && x1 < 6) && (0 <= y1 && y1 < 3) && m_thingGrid[x1][y1] &&
		(
		(m_thingGrid[x1][y1]->getColorType() == m_thingGrid[0][1]->getColorType()) ||
		(m_thingGrid[x1][y1]->getColorType() == m_thingGrid[0][2]->getColorType()) ||
		(m_thingGrid[x1][y1]->getColorType() == m_thingGrid[0][3]->getColorType())
		)
		)
	{
		// �������ʱ��û�п�ʼ����ʼ����ʱ
		if (!m_isRunning)
		{
			m_isRunning = true;
			TimeManager::getInstance()->startCountDown();
		}
		// * add animation
		auto flower = m_thingGrid[x1][y1];
		log("farmer pos x = %f, y = %f", flower->getPosition().x, flower->getPosition().y);

		Blink* blink = Blink::create(3.0f, 3);

		flower->runAction(blink);

		// ��վ����еĻ���ָ��
		m_thingGrid[x1][y1] = nullptr;

		
		if (getLivingFarmersNum() <= 0 && m_loop <= 0)
		{
			_eventDispatcher->dispatchCustomEvent("tollgate_clear", (void*)"EatFlowers");
			CCLOG("EatFlowers clear");
		}

		//flower->runAction(createAnimate());

		flower->tapped();

	}
	return true;
}

int CheckThethingGrid::getLivingFarmersNum()
{
	int count = 0;
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			if (m_thingGrid[x][y] != nullptr &&
				((m_thingGrid[x][y]->getColorType() != m_thingGrid[0][1]->getColorType()) ||
				(m_thingGrid[x][y]->getColorType() != m_thingGrid[0][2]->getColorType()) ||
				(m_thingGrid[x][y]->getColorType() != m_thingGrid[0][3]->getColorType())))
				count++;
		}
	}

	/*
	if (m_flowersesGrid[3][1] != nullptr)
	{
	count--;
	}
	*/

	//count--;
	count = count - 3;
	return count;
}

void CheckThethingGrid::generateNewZerglingGrid(const int diff)
{
	m_loop--;
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			m_thingGrid[x][y] = createflower((farmerandflower::FlowerColor)c_g[diff][y][x], x, y);
		}
	}
}








