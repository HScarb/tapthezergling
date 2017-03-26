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

void RunScene::setRun()
{
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
	auto scene = Scene::create();
	auto layer = RunScene::create(diff, loop);
	scene->addChild(layer);
	return scene;
}

bool RunScene::init(int diff, int loop)
{
	if (!Layer::init())
		return false;

	auto UI = CSLoader::createNode("Tollgates/RunScene.csb");
	addChild(UI);

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

	//RepeatForever创建重复动作
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
	if (!m_isRunning)
	{
		m_isRunning = true;
		TimeManager::getInstance()->startCountDown();
	}
	auto x1 = m_meteorolite->getPositionX(); auto x3 = m_meteorolite2->getPositionX(); auto x4 = m_meteorolite3->getPositionX();
	auto y1 = m_meteorolite->getPositionY(); auto y3 = m_meteorolite2->getPositionY(); auto y4 = m_meteorolite3->getPositionY();

	//设置获取陨石位置，如果与小狗的位置重叠，则减少时间（或者倒退一定距离）
	auto x2 = m_zeriling_sprite->getPositionX();
	auto y2 = m_zeriling_sprite->getPositionY();

	if ((abs(x1 - x2) <= 35 && abs(y1 - y2) <= 35) || (abs(x3 - x2) <= 35 && abs(y3 - y2) <= 35) || (abs(x4 - x2) <= 35 && abs(y4 - y2) <= 35))
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
FlowWord *flowword = FlowWord::create();  
    this->addChild(flowword);  
    flowword->showWord("-15",GetSprite()->getPosition());  
	使用方法*/
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