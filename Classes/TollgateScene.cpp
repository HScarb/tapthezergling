// TollgateScene.cpp
#include "TollgateScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "GameManager.h"
#include "Global.h"
#include "SimpleAudioEngine.h"
#include "SoundManager.h"
#include "MainScene.h"
#include "CardControlLayer.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace CocosDenshion;

cocos2d::Scene* TollgateScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TollgateScene::create();
	scene->addChild(layer);
	return scene;
}

int o = 0;   //调试用宝石能量数量初始化
int p = 0;
bool act = false;    //初始化宝箱调试

bool TollgateScene::init()
{
	if (!Layer::init())
		return false;
	m_energyText = nullptr;
	m_jewelText = nullptr;
	m_addJewelBtn = nullptr;
	m_cardBtn = nullptr;
	m_homeBtn = nullptr;
	m_energyBar = nullptr;
	m_timeText = nullptr;
	m_timeBar = nullptr;
	m_chest_sprite = nullptr;
	m_label = nullptr;

	m_scrollView = nullptr;
	m_t1 = nullptr;
	m_t2 = nullptr;
	m_t3 = nullptr;

	m_tollgateNumLabel = nullptr;

	// 加载UI
	auto rootNode = CSLoader::createNode("TollgateScene.csb");
	addChild(rootNode);

	//创建宝箱
	setChest();

	//加载卡片合成层
	m_cardLayer = CardControlLayer::create();
	this->addChild(m_cardLayer,1);
	m_cardLayer->setVisible(false);

	// tollgate Num label
	m_tollgateNumLabel = Label::createWithTTF(StringUtils::format("%d", GameManager::getInstance()->getTollgateNum()), "fonts/AveriaSansLibre-Bold.ttf", 50);
	m_tollgateNumLabel->setPosition(486, 70);
	this->addChild(m_tollgateNumLabel);

	// 载入其他
	m_energyText = (Text*)(rootNode->getChildByName("Text_energy"));
	m_jewelText = (Text*)(rootNode->getChildByName("Text_jewel"));
	m_homeBtn = (Button*)(rootNode->getChildByName("Button_home"));
	m_cardBtn = (Button*)(rootNode->getChildByName("Button_cards"));
	// m_addJewelBtn = (Button*)(rootNode->getChildByName(""));
	m_energyBar = (LoadingBar*)(rootNode->getChildByName("LoadingBar_energy"));
	m_timeText = (Text*)rootNode->getChildByName("Text_time");
	m_timeBar = (LoadingBar*)rootNode->getChildByName("LoadingBar_time");

	m_scrollView = (ScrollView*)(rootNode->getChildByName("ScrollView"));
	m_t1 = (Text*)(m_scrollView->getChildByName("Text_1"));
	m_t2 = (Text*)(m_scrollView->getChildByName("Text_2"));
	m_t3 = (Text*)(m_scrollView->getChildByName("Text_3"));
	m_t4 = (Text*)(m_scrollView->getChildByName("Text_4"));
	m_t5 = (Text*)(m_scrollView->getChildByName("Text_5"));
	m_t6 = (Text*)(m_scrollView->getChildByName("Text_6"));
	m_t7 = (Text*)(m_scrollView->getChildByName("Text_7"));
	m_t8 = (Text*)(m_scrollView->getChildByName("Text_8"));
	m_t9 = (Text*)(m_scrollView->getChildByName("Text_9"));
	m_t10 = (Text*)(m_scrollView->getChildByName("Text_10"));
	
	/* !!!设置关卡目录不显示，当调试的时候可以设置为显示 */
	m_scrollView->setVisible(false);

	//关键地方
	m_energyText->setText("0");
	m_jewelText->setText("0");
	m_energyBar->setPercent(10.0f);
	m_timeBar->setPercent(100.0f);
	m_timeText->setText("00.00");
	
	// 设置时间
	if (GameManager::getInstance()->getIsGameOn() == false)		// 如果游戏还没有开始
	{
		TimeManager::getInstance()->setTime(INITIAL_TIME);
		GameManager::getInstance()->setIsGameOn(true);			// set game is on
		m_timeText->setText(StringUtils::format("%05.2f", TimeManager::getInstance()->getTime()));		// 设置时间标签按照格式显示时间

		setNextTollgate();		// 随机下一关
	}
	else
	{
		m_timeText->setText(StringUtils::format("%05.2f", TimeManager::getInstance()->getTime()));		// 设置时间标签按照格式显示时间
		m_timeBar->setPercent(TimeManager::getInstance()->getTime() / TimeManager::getInstance()->getPreTime() * 100.0f);		// 设置时间进度条进度

		if (GameManager::getInstance()->getIsWaitToAddTime())
		{
			addSeconds();
			CCLOG("added 2 seconds.");
			GameManager::getInstance()->setIsWaitToAddTime(false);
		}
		else
			showNextTollgate();
	}

	// 关联触摸函数
	m_homeBtn->addTouchEventListener(this, toucheventselector(TollgateScene::onHomeBtnClicked));
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TollgateScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(TollgateScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	m_t1->addTouchEventListener(this, toucheventselector(TollgateScene::onItem1Clicked));
	m_t2->addTouchEventListener(this, toucheventselector(TollgateScene::onItem2Clicked));
	m_t3->addTouchEventListener(this, toucheventselector(TollgateScene::onItem3Clicked));
	m_t4->addTouchEventListener(this, toucheventselector(TollgateScene::onItem4Clicked));
	m_t5->addTouchEventListener(this, toucheventselector(TollgateScene::onItem5Clicked));
	m_t6->addTouchEventListener(this, toucheventselector(TollgateScene::onItem6Clicked));
	m_t7->addTouchEventListener(this, toucheventselector(TollgateScene::onItem7Clicked));
	m_t8->addTouchEventListener(this, toucheventselector(TollgateScene::onItem8Clicked));
	m_t9->addTouchEventListener(this, toucheventselector(TollgateScene::onItem9Clicked));
	m_t10->addTouchEventListener(this, toucheventselector(TollgateScene::onItem10Clicked));
	m_cardBtn->addTouchEventListener(this, toucheventselector(TollgateScene::onCardBtnClicked));

//	SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/MainMenu.mp3", true);
	SoundManager::getInstance()->playMenuMusic();

	return true;
}

void TollgateScene::addDiamond()
{
	int i = random(1, 9);
	o = o + i;
	m_jewelText->setText(StringUtils::format("%d", o));
}

void TollgateScene::addEnergy()
{
	int i = random(1, 9);
	p = p + i;
	m_energyText->setText(StringUtils::format("%d", p));
}

/*
void TollgateScene::removethis()
{
	auto child = getChildByTag(2);
	child->removeChild(child, true);

	getTestSuite()->enterNextTest();
}
*/

void TollgateScene::callBack1()			//定义函数，该函数会在MoveTo动作结束后被调用。
{
	addEnergy();
}

void TollgateScene::callBack2()
{
	addDiamond();
}

void TollgateScene::callBack3()
{
	auto child = getChildByTag(2);
	FadeOut * fadeout = FadeOut::create(0.01);
	child->runAction(fadeout);
}

void TollgateScene::callBack4()
{
	setChest();
}

void TollgateScene::setChest()
{
	//创建宝箱及宝箱出场动作
	auto visibleSize = Director::getInstance()->getVisibleSize();
	m_chest_sprite = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("res/images/chest/chest1.png"));
	m_chest_sprite->setPosition(visibleSize.width / 2 + 50, visibleSize.height / 2);
	m_chest_sprite->setScale(0.65, 0.65);
	this->addChild(m_chest_sprite, 2);

	JumpTo * jumpto = JumpTo::create(1, ccp(visibleSize.width / 2, visibleSize.height / 2), 50, 2);
	m_chest_sprite->runAction(jumpto);
}

void TollgateScene::addSeconds()
{
	auto swooth = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey(PATH_BUTTON_ACCEPT_1));
	swooth->setPosition(CENTER);
	swooth->setScale(0.0);
	auto delay0 = DelayTime::create(0.3);
	auto big1 = ScaleTo::create(0.35, 0.5);
	auto delay1 = DelayTime::create(0.35);
	auto small1 = ScaleTo::create(0.35, 0.0);
	auto callFunc1 = CallFunc::create([swooth]()
	{
		swooth->setTexture(TextureCache::getInstance()->getTextureForKey(PATH_ADD_TWO));
	});
	auto big2 = ScaleTo::create(0.35, 0.5);
	auto delay2 = DelayTime::create(0.35);
	auto small2 = ScaleTo::create(0.2, 0.0);
	auto moveBy = MoveBy::create(0.25, Vec2(0, 100));
	auto callFunc2 = CallFunc::create([=]()
	{
		swooth->removeFromParent();
		TimeManager::getInstance()->addTime(2.0f);				// add 2 seconds
		m_timeText->setText(StringUtils::format("%05.2f", TimeManager::getInstance()->getTime()));		// 设置时间标签按照格式显示时间
		m_timeBar->setPercent(100);
		setNextTollgate();
	});
	
	this->addChild(swooth);
	swooth->runAction(Sequence::create(delay0, big1, delay1, small1, callFunc1, big2, delay2, Spawn::createWithTwoActions(small2, moveBy), callFunc2, nullptr));
	
}

void TollgateScene::setNextTollgate()
{
	int r = 0;
	// 如果第一次随机，之前没有关卡
	if(GameManager::getInstance()->getTollgate() == 0)
	{
		r = random(2, TOTAL_TOLLGATE_TYPE);
		GameManager::getInstance()->setNextTollgate(r);
	}
	// 如果之前有关卡
	else
	{
		do
		{
			r = random(1, TOTAL_TOLLGATE_TYPE);
		} while (r == GameManager::getInstance()->getTollgate());
		GameManager::getInstance()->setNextTollgate(r);
	}
	CCLOG("Current Tollgate Num %d", GameManager::getInstance()->getTollgateNum());
	showNextTollgate();
}

void TollgateScene::showNextTollgate()
{
	int r = GameManager::getInstance()->getNextTollgate();
	int num = GameManager::getInstance()->getTollgateNum();
	Label * label = nullptr;
	// 显示关卡简介
	if (num % 10 == 0)
	{
				label = Label::createWithTTF(BOSS_TOLLGATE_NAME[num / 10], "fonts/msyh.ttf", 40);
//		label = Label::create(BOSS_TOLLGATE_NAME[num / 10].c_str(), "Microsoft YaHei", 40);
	}
	else
				label = Label::createWithTTF(TOLLGATE_NAME[r], "fonts/msyh.ttf", 40);
//		label = Label::createWithSystemFont(, "Microsoft YaHei", 40);

	auto menuItemLabel = MenuItemLabel::create(label, CC_CALLBACK_1(TollgateScene::onTollgateLabelClicked, this));
	auto menu = Menu::create(menuItemLabel, nullptr);
	menu->setPosition(CENTER);
	this->addChild(menu);

	auto scale1 = ScaleTo::create(0.2, 0.0);
	auto changeText = CallFunc::create([this]()
	{
		m_tollgateNumLabel->setString(StringUtils::format("%d", GameManager::getInstance()->getTollgateNum()));
	});
	auto scale2 = ScaleTo::create(0.2, 1.0);
	m_tollgateNumLabel->runAction(Sequence::create(scale1, changeText, scale2, nullptr));
}

//创建开箱子的动画
cocos2d::Animate* TollgateScene::m_createAnimate()
{
		int iFrameNum = 2;
		SpriteFrame * frame = NULL;
		Vector<SpriteFrame*> frameVec;

		for (int i = 1; i <= 2; i++)
		{
			frame = SpriteFrame::create(StringUtils::format("res/images/chest/chest%d.png", i), Rect(0, 0, 256, 256));
			frameVec.pushBack(frame);
		}
		Animation* animation = Animation::createWithSpriteFrames(frameVec);
		animation->setLoops(1);
		animation->setDelayPerUnit(0.05f);
		Animate* action = Animate::create(animation);

		return action;
}

void TollgateScene::onHomeBtnClicked(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::MainScene);
	}	
}

void TollgateScene::onCardBtnClicked(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		log("CardLayer");
		m_cardLayer->setVisible(true);
	}
}

void TollgateScene::onTollgateLabelClicked(Ref* pSender)
{
	int nextTollgate = GameManager::getInstance()->getNextTollgate();
	int num = GameManager::getInstance()->getTollgateNum();
	if(num % 10 == 0)
	{
		SceneManager::getInstance()->changeScene((SceneManager::SceneType)(100 + num / 10));
	}
	else 
	{
		GameManager::getInstance()->setTollgate(nextTollgate);
		CCLOG("Tollgate %d change scene...", nextTollgate);
		int diff = GameManager::getInstance()->getDiff();
		int loop = GameManager::getInstance()->getLoop();
		SceneManager::getInstance()->changeScene((SceneManager::TollgateSceneType)nextTollgate, diff, loop);
	}
}

void TollgateScene::onItem1Clicked(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED) 
	{
		log("tollgate 1");
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::DoubleTapScene, 0, 3);
	}
}

void TollgateScene::onItem2Clicked(Ref* pSender, TouchEventType type)
{
	if(type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		log("tollgate 2");
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::SlideCutScene, 0, 2);

	}
}

void TollgateScene::onItem3Clicked(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		log("tollgate 3");
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::EatCandiesScene, 0, 1);
	}
}
void TollgateScene::onItem4Clicked(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		log("tollgate 4");
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::BurrowAndAttackScene, 0, 2);
	}
}

void TollgateScene::onItem5Clicked(Ref* pSender, TouchEventType type)
{
	if(type == TOUCH_EVENT_ENDED)
	{
		log("tollgate 5");
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::JumpingOnPoolScene, 1, 2);
	}
}

void TollgateScene::onItem6Clicked(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		log("tollgate 6");
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::ClassifyUnits, 1, 2);
	}
}

void TollgateScene::onItem7Clicked(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if(type == TOUCH_EVENT_ENDED)
	{
		log("tollgate 7");
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::BOSS1);
	}
}

void TollgateScene::onItem8Clicked(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if(type == TOUCH_EVENT_ENDED)
	{
		log("tollgate 8");
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::BOSS2);
	}
}

void TollgateScene::onItem9Clicked(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		log("tollgate 9");
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::CheckThethingScene, 2, 2);
	}
}


void TollgateScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{	
		auto pos = touch->getLocationInView();
		auto visibleSize = Director::getInstance()->getVisibleSize();

		//闪光
		Sprite* m_flash = Sprite::create("res/images/chest/flash.png");
		m_flash->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		m_flash->setScale(0.65, 0.65);
		m_flash->setVisible(false);
		this->addChild(m_flash, 1);

		RotateTo *rotateTo = RotateTo::create(2, 100);
		ScaleBy *scaleBy = ScaleBy::create(1.8, 1.8);
		Hide *hideAction = Hide::create();
		ScaleTo * scaleto2 = ScaleTo::create(0.3, 0.000001);
		Sequence * seq1 = Sequence::create(DelayTime::create(2.3), scaleto2, NULL);
		Sequence * seq2 = Sequence::create(DelayTime::create(2.3), hideAction, NULL);


		if (m_chest_sprite->getBoundingBox().containsPoint(pos))
		{
			//打开宝箱时触发文字（需要设置条件）
			if (act != true)
			{
				Label *m_label = Label::create("Do great! Please get a reward", "Skranji-Bold", 40);
				m_label->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 100);
				this->addChild(m_label, 1);
			}

			m_flash->setVisible(true);
			m_flash->runAction(rotateTo);
			m_flash->runAction(scaleBy);
			m_chest_sprite->runAction(m_createAnimate());
			m_chest_sprite->runAction(seq1);
			m_flash->runAction(seq2);

			int i = random(1, 2);
			if (i == Energy)
			{
				//创建能量
				m_energy_sprite = Sprite::create("res/images/chest/Energy.png");
				m_energy_sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
				m_energy_sprite->setScale(0.48, 0.48);
				addChild(m_energy_sprite, 1, 2);

				//能量提取
				auto action = Sequence::create(
					DelayTime::create(3.45f),
					MoveBy::create(1, ccp(-420, 220)),
					CallFunc::create(CC_CALLBACK_0(TollgateScene::callBack1, this)),
					DelayTime::create(0.05f),
					CallFunc::create(CC_CALLBACK_0(TollgateScene::callBack3, this)),
					CallFunc::create(CC_CALLBACK_0(TollgateScene::callBack4, this)),
					nullptr
					);
				m_energy_sprite->runAction(action);
			}
			else if (i == Jewel)
			{
				//创建宝石
				m_diamond_sprite = Sprite::create("res/images/chest/Gem.png");
				m_diamond_sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
				m_diamond_sprite->setScale(0.48, 0.48);
				addChild(m_diamond_sprite, 1, 2);

				//宝石提取
				auto action = Sequence::create(
					DelayTime::create(3.45f),
					MoveBy::create(1, ccp(280, 220)),
					CallFunc::create(CC_CALLBACK_0(TollgateScene::callBack2, this)),
					DelayTime::create(0.05f),
					CallFunc::create(CC_CALLBACK_0(TollgateScene::callBack3, this)),
					CallFunc::create(CC_CALLBACK_0(TollgateScene::callBack4,this)),
					nullptr
					);
				m_diamond_sprite->runAction(action);
			}
			else if (i == Card)
			{
				//随机创建卡片
			}
			act = true;
		}

}

bool TollgateScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	return true;
}

void TollgateScene::onItem10Clicked(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		log("tollgate 10");
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::FeedSnacks, 0, 2);
	}
}