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

int w = 0;   //test

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
	w = 0;
	setRun();
	m_isRunning = false;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchEnded = CC_CALLBACK_2(RunScene::onTouchEnded, this);
	listener->onTouchBegan = CC_CALLBACK_2(RunScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

cocos2d::Animate* RunScene::m_createAnimate()
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
	if (m_zeriling_sprite->getBoundingBox().containsPoint(pos))
	{
		MoveBy *moveby = MoveBy::create(0.2, ccp(80, 0));
		FlowWord *flowword = FlowWord::create();
		this->addChild(flowword);
		flowword->showWord("Wow!!", m_zeriling_sprite->getPosition());
		m_zeriling_sprite->runAction(Spawn::create(moveby, m_createAnimate(), NULL));
		w++;
			if (w == 10)
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

void FlowWord::showWord(const char* text, CCPoint pos) 
{
	m_textLab->setString(text);
	m_textLab->setPosition(pos);
	m_textLab->setVisible(true);

	/* 组合两个动作，放大后缩小 */
	CCActionInterval* scaleLarge = CCScaleTo::create(0.3f, 2.5f, 2.5f);
	CCActionInterval* scaleSmall = CCScaleTo::create(0.5f, 0.5f, 0.5f);

	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(FlowWord::flowEnd));

	CCActionInterval* actions = CCSequence::create(scaleLarge, scaleSmall, callFunc, NULL);

	m_textLab->runAction(actions);
}

void FlowWord::flowEnd() 
{
	/* 动作结束，从父节点中删除自身 */
	m_textLab->setVisible(false);
	m_textLab->removeFromParentAndCleanup(true);
}