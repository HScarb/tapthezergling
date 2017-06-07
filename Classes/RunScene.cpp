#include "RunScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include "TollgateControlLayer.h"
#include "Global.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

int STEP = 0;   //test
const int MAX_STEP = 10;

void RunScene::getPosition(float dt)
{
	//注：(x0,x0)是小狗的位置，其余是陨石的位置
	Position_x0 = m_zeriling_sprite->getPositionX(); Position_x1 = m_meteorolite->getPositionX(); Position_x2 = m_meteorolite2->getPositionX(); Position_x3 = m_meteorolite3->getPositionX();
	Position_y0 = m_zeriling_sprite->getPositionY(); Position_y1 = m_meteorolite->getPositionY(); Position_y2 = m_meteorolite2->getPositionY(); Position_y3 = m_meteorolite3->getPositionY();
}

void RunScene::onEnter()
{
	Layer::onEnter();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//创建一个物理世界, 大小和屏幕的尺寸相同, 使用默认材质, debug框的宽度为3个像素
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	//创建一个碰撞图形
	auto edgeShape = Node::create();
	//将图形和刚刚创建的世界绑定
	edgeShape->setPhysicsBody(body);
	//设置图形的位置在屏幕正中间
	edgeShape->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//添加进图层
	addChild(edgeShape);
}

void RunScene::setRun()
{
	//物理世界部分
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(320, 300);
	b2Body *zeriling = world->CreateBody(&bodyDef);
	zeriling->SetUserData(m_zeriling_sprite);
	zeriling->SetActive(true);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	m_zeriling_sprite = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("res/Res/ZerlingAnimation/r_1.png"));
	m_zeriling_sprite->setScale(1.1);
	m_zeriling_sprite->setPosition(100, visibleSize.height / 2 + 10);
	this->addChild(m_zeriling_sprite);
}

cocos2d::Layer* RunScene::create(int diff, int loop)
{
	auto pRef = new RunScene();
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

cocos2d::Scene* RunScene::createScene(int diff, int loop)
{
	Scene *scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = RunScene::create(diff, loop);
	scene->addChild(layer);
	return scene;

	/*auto scene = Scene::create();
	auto layer = RunScene::create(diff, loop);
	scene->addChild(layer);
	return scene;*/
}

bool RunScene::init(int diff, int loop)
{
	if (!Layer::init())
		return false;

	auto UI = CSLoader::createNode("Tollgates/RunScene.csb");
	addChild(UI);

	b2Vec2 gravity;
	gravity.Set(0.0f, -2.0f);
	world = new b2World(gravity);
	world->SetContinuousPhysics(true);

	m_controlLayer = TollgateControlLayer::create();
	m_controlLayer->initTimeBar();
	m_controlLayer->scheduleUpdate();
	addChild(m_controlLayer, ZORDER_TOLLGATECONTROLLAYER);

	m_pauseBtn = (Button*)(UI->getChildByName("Button_pause"));
	m_timeBar = (LoadingBar*)(UI->getChildByName("LoadingBar_time"));
	m_timeText = (Text*)(UI->getChildByName("Text_time"));

	//初始化奔跑的小狗
	STEP = 0;
	setRun();
	m_isRunning = false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	m_meteorolite = nullptr;
	m_meteorolite = Sprite::create("res/Res/Runrunrun/yunshi.png");
	m_meteorolite->setScale(0.3, 0.3);
	m_meteorolite->setPosition(visibleSize.width / 2 + 20,visibleSize.height - 50);
	this->addChild(m_meteorolite);

	m_meteorolite2 = nullptr;
	m_meteorolite2 = Sprite::create("res/Res/Runrunrun/yunshi2.png");
	m_meteorolite2->setScale(0.3, 0.3);
	m_meteorolite2->setPosition(visibleSize.width / 2 - 70,visibleSize.height - 50);
	this->addChild(m_meteorolite2);

	m_meteorolite3 = nullptr;
	m_meteorolite3 = Sprite::create("res/Res/Runrunrun/yunshi3.png");
	m_meteorolite3->setScale(0.3, 0.3);
	m_meteorolite3->setPosition(visibleSize.width / 2 + 120, visibleSize.height - 50);
	this->addChild(m_meteorolite3);

	//物理世界部分
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(320, 300);
	b2Body *stone1 = world->CreateBody(&bodyDef);
	b2Body *stone2 = world->CreateBody(&bodyDef);
	b2Body *stone3 = world->CreateBody(&bodyDef);
	stone1->SetUserData(m_meteorolite);
	stone1->SetActive(true);
	stone2->SetUserData(m_meteorolite2);
	stone2->SetActive(true);
	stone3->SetUserData(m_meteorolite3);
	stone3->SetActive(true);

	Position_x0 = m_zeriling_sprite->getPositionX(); 
	Position_x1 = m_meteorolite->getPositionX(); Position_x2 = m_meteorolite2->getPositionX(); Position_x3 = m_meteorolite3->getPositionX();
	Position_y0 = m_zeriling_sprite->getPositionY(); 
	Position_y1 = m_meteorolite->getPositionY(); Position_y2 = m_meteorolite2->getPositionY(); Position_y3 = m_meteorolite3->getPositionY();

	MoveBy *moveby1 = MoveBy::create(3, Vec2(0,-480));
	MoveBy *moveby2 = MoveBy::create(5, Vec2(0,-480));
	MoveBy *moveby3 = MoveBy::create(2, Vec2(0, -480));
	auto action = RepeatForever::create(
		Sequence::create(moveby1->clone(), moveby1->reverse(), nullptr)
		);
	auto action2 = RepeatForever::create(
		Sequence::create(moveby2->clone(), moveby2->reverse(), nullptr)
		);
	auto action3 = RepeatForever::create(
		Sequence::create(moveby3->clone(), moveby3->reverse(), nullptr)
		);
	m_meteorolite->runAction(action);
	m_meteorolite2->runAction(action2);
	m_meteorolite3->runAction(action3);


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchEnded = CC_CALLBACK_2(RunScene::onTouchEnded, this);
	listener->onTouchBegan = CC_CALLBACK_2(RunScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [](PhysicsContact &contact)
	{
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener,this);

	return true;
}

cocos2d::Animate* RunScene::createAnimate()
{
	int iFrameNum = 4;
	SpriteFrame * frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = 1; i <= 4; i++)
	{
		frame = SpriteFrame::create(StringUtils::format("res/Res/ZerlingAnimation/r_%d.png", i), Rect(0, 0, 128, 128));
		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);
	Animate* action = Animate::create(animation);

	return action;
}

void RunScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	//FlowWord* flowWord = FlowWord::create();
}

bool RunScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	auto pos = touch->getLocation();
	int x = (int)pos.x;
	int y = (int)pos.y;
	log("%d,%d", x, y);
	/*if (!m_isRunning)
	{
		m_isRunning = true;
		TimeManager::getInstance()->startCountDown();
	}*/
	
	schedule(schedule_selector(RunScene::getPosition, 0.2f));

	if ((abs(Position_x1 - Position_x0) <= 40 && abs(Position_y1 - Position_y0) <= 40) || (abs(Position_x2 - Position_x0) <= 42 && abs(Position_y2 - Position_y0) <= 42) || (abs(Position_x3 - Position_x0) <= 40 && abs(Position_y3 - Position_y0) <= 40))
	{							
		m_zeriling_sprite->runAction(MoveBy::create(0.2, Vec2(-240, 0)));
		STEP = STEP - 3;
	}

	if (m_zeriling_sprite->getBoundingBox().containsPoint(pos))
	{
		MoveBy *moveby = MoveBy::create(0.4, ccp(80, 0));
		FlowWord *flowword = FlowWord::create();
		this->addChild(flowword);
		flowword->showWord("Woo!", m_zeriling_sprite->getPosition());
		m_zeriling_sprite->runAction(Spawn::create(moveby, createAnimate(), NULL));
		STEP++;
		if (STEP == MAX_STEP)//跳10次到达终点
		{
			_eventDispatcher->dispatchCustomEvent("tollgate_clear", (void*)"Runrunrun");
			CCLOG("Runrunrun clear");
		}
	}

	return true;
}


/*
	使用方法:
	FlowWord *flowword = FlowWord::create();  
    this->addChild(flowword);  
    flowword->showWord("-15",GetSprite()->getPosition());  
*/
FlowWord* FlowWord::create()
{
	FlowWord* flowWord = new FlowWord();

	if (flowWord && flowWord->init()) {
		flowWord->autorelease();
	}
	else {
		CC_SAFE_DELETE(flowWord);
	}

	return flowWord;
}

bool FlowWord::init() 
{
	m_textLab = CCLabelTTF::create("", "AveriaSansLibre-Bold", 20);
	m_textLab->setColor(ccc3(255, 0, 0));
	m_textLab->setAnchorPoint(ccp(1, 0));
	m_textLab->setVisible(false);

	this->addChild(m_textLab);
	return true;
}

void FlowWord::showWord(const char* text, Vec2 pos) 
{
	m_textLab->setString(text);
	m_textLab->setPosition(pos);
	m_textLab->setVisible(true);

	/* 组合两个动作，放大后缩小 */
	ActionInterval* scaleLarge = ScaleTo::create(0.3f, 2.5f, 2.5f);
	ActionInterval* scaleSmall = ScaleTo::create(0.5f, 0.5f, 0.5f);

	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(FlowWord::flowEnd));

	ActionInterval* actions = Sequence::create(scaleLarge, scaleSmall, callFunc, NULL);

	m_textLab->runAction(actions);
}

void FlowWord::flowEnd() 
{
	/* 动作结束，从父节点中删除自身 */
	m_textLab->setVisible(false);
	m_textLab->removeFromParentAndCleanup(true);
}