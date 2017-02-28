// TollgateScene.cpp
//#define _CRT_SECURE_NO_DEPRECATE      
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
#include "DataManager.h"
#include "CardManager.h"
#include "Card.h";

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

void TollgateScene::runCard()
{
	auto action = Sequence::create(
		MoveBy::create(1, ccp(420, -220)),
		CallFunc::create([this]
			{
				addCard();
			}),
		DelayTime::create(0.05f),
		CallFunc::create([this]
			{
				FadeOut* fadeout = FadeOut::create(0.01);
				m_rewardCard->runAction(fadeout);
			}),
		CallFunc::create([this]
			{
				if (!m_res)
					m_cardBtn->runAction(MoveBy::create(0.5, Point(0, -120)));
			}),
		CallFunc::create([this]
			{
				if (!m_res)
					m_goOnBtn->runAction(MoveBy::create(0.5, Point(0, 120)));
				m_res = true; //res为ture,则箭头在上面
			}),
		CallFunc::create([this]
			{
				setChest();
			}),
		CallFunc::create([this]
			{
				int e = random(10, 12);
				m_money = e * m_chestOpenTimes;
				m_anotherChestText->setText(StringUtils::format("Need %d extra diamond", e * m_chestOpenTimes));
				m_anotherChestText->setVisible(true);
				m_act = false;
				auto child = getChildByTag(2); //隐藏GERAT，GREAT的Tag是2
				child->removeFromParent();
			}),
		nullptr
	);
	m_rewardCard->runAction(action);
}

void TollgateScene::runEnergy()
{
	auto action = Sequence::create(
		MoveBy::create(1, ccp(-420, 220)),
		CallFunc::create([this]
			{
				addEnergy();
			}),
		DelayTime::create(0.05f),
		CallFunc::create([this]
			{
				FadeOut* fadeout = FadeOut::create(0.01);
				m_energy_sprite->runAction(fadeout);
			}),
		CallFunc::create([this]
			{
				if (!m_res) //现在是false,卡片在上面
					m_cardBtn->runAction(MoveBy::create(0.5, Point(0, -120)));
			}),
		CallFunc::create([this]
			{
				if (!m_res)
					m_goOnBtn->runAction(MoveBy::create(0.5, Point(0, 120)));
				m_res = true; //res为ture,则箭头在上面
			}),
		CallFunc::create([this]
			{
				setChest();
			}),
		CallFunc::create([this]
			{
				int e = random(10, 12);
				m_money = e * m_chestOpenTimes;
				m_anotherChestText->setText(StringUtils::format("Need %d extro diamond", e * m_chestOpenTimes));
				m_anotherChestText->setVisible(true);
				m_act = false;
				auto child = getChildByTag(2); //隐藏GERAT，GREAT的Tag是2
				child->removeFromParent();
			}),
		nullptr
	);
	m_energy_sprite->runAction(action);
}

void TollgateScene::runDiamond()
{
	auto action = Sequence::create(
		MoveBy::create(1, ccp(280, 220)),
		CallFunc::create([this]
			{
				addDiamond();
			}),
		DelayTime::create(0.05f),
		CallFunc::create([this]
			{
				FadeOut* fadeout = FadeOut::create(0.01);
				m_diamond_sprite->runAction(fadeout);
			}),
		CallFunc::create([this]
			{
				if (!m_res)
					m_cardBtn->runAction(MoveBy::create(0.5, Point(0, -120)));
			}),
		CallFunc::create([this]
			{
				if (!m_res)
					m_goOnBtn->runAction(MoveBy::create(0.5, Point(0, 120)));
				m_res = true; //此时，箭头在上面
			}),
		CallFunc::create([this]
			{
				setChest();
			}),
		CallFunc::create([this]
			{
				int e = random(10, 12);
				m_money = e * m_chestOpenTimes;
				m_anotherChestText->setText(StringUtils::format("Need %d extro diamond", e * m_chestOpenTimes)); //这个地方，m是全局变量，e不是
				m_anotherChestText->setVisible(true);
				m_act = false;
				auto child = getChildByTag(2); //隐藏GERAT，GREAT的Tag是2
				child->removeFromParent();
			}),
		nullptr
	);
	m_diamond_sprite->runAction(action);
}

bool TollgateScene::init()
{
	if (!Layer::init())
		return false;
	m_chestOpenTimes = 0;
	m_act = false;
	m_but = false;
	m_res = false;
	m_pre = false;
	m_money = 0;
	m_energyText = nullptr;
	m_jewelText = nullptr;
	m_addJewelBtn = nullptr;
	m_cardBtn = nullptr;
	m_homeBtn = nullptr;
	m_goOnBtn = nullptr;
	m_energyBar = nullptr;
	m_timeText = nullptr;
	m_timeBar = nullptr;
	m_chest_sprite = nullptr;
	m_energy_sprite = nullptr;
	m_diamond_sprite = nullptr;
	m_rewardCard = nullptr;
	m_flash = nullptr;
	m_label = nullptr;
	m_anotherChestText = nullptr;
	m_currentTime = nullptr;

	if (!m_chest_sprite)
	{
		m_chest_sprite = nullptr;
	}

	//初始宝箱开启设置为0次
	m_chestOpenTimes = 0;

	//这个按钮是用来不重复生成关卡的
	m_but = false;
	m_act = false;

	m_scrollView = nullptr;
	m_t1 = nullptr;
	m_t2 = nullptr;
	m_t3 = nullptr;

	m_tollgateNumLabel = nullptr;

	// 加载UI
	auto rootNode = CSLoader::createNode("TollgateScene.csb");
	addChild(rootNode);

	/*//加载卡片合成层
	m_cardControlLayer = CardControlLayer::create();
	this->addChild(m_cardControlLayer, 11);
	m_cardControlLayer->setVisible(false);
*/
	// tollgate Num label
	m_tollgateNumLabel = Label::createWithTTF(StringUtils::format("%d", GameManager::getInstance()->getTollgateNum()), "fonts/AveriaSansLibre-Bold.ttf", 50);
	m_tollgateNumLabel->setPosition(486, 70);
	this->addChild(m_tollgateNumLabel);
	// 载入其他
	m_energyText = (Text*)(rootNode->getChildByName("Text_energy"));
	m_jewelText = (Text*)(rootNode->getChildByName("Text_jewel"));
	m_homeBtn = (Button*)(rootNode->getChildByName("Button_home"));
	m_cardBtn = (Button*)(rootNode->getChildByName("Button_cards"));
	m_goOnBtn = (Button*)(rootNode->getChildByName("Button_goon"));
	// m_addJewelBtn = (Button*)(rootNode->getChildByName(""));
	m_energyBar = (LoadingBar*)(rootNode->getChildByName("LoadingBar_energy"));
	m_timeText = (Text*)rootNode->getChildByName("Text_time");
	m_timeBar = (LoadingBar*)rootNode->getChildByName("LoadingBar_time");
	
	/*m_goonBtn->setVisible(false);*/

	m_anotherChestText = (Text*)rootNode->getChildByName("Chest_numText");
	//m_anotherChestText->setVisible(false);

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
	m_t11 = (Text*)(m_scrollView->getChildByName("Text_11"));
	m_t12 = (Text*)(m_scrollView->getChildByName("Text_12"));
	
	/* !!!设置关卡目录不显示，当调试的时候可以设置为显示 */
	m_scrollView->setVisible(false);

	//关键地方
	m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
	m_jewelText->setText(StringUtils::format("%d", GameManager::getInstance()->getJewel()));
	m_energyBar->setPercent(10.0f);
	m_timeBar->setPercent(100.0f);
	m_timeText->setText("00.00");
	
	/*m_currentTime = getCurrentTime();
	while (GameManager::getInstance()->getEnergy() < 30)
	{
		DataManager::getInstance()->setLasttime(m_currentTime);
		int s = m_currentTime->tm_min;			//这个值是实时变化的
		if (s>0)
		{
			GameManager::getInstance()->setEnergy(GameManager::getInstance()->getEnergy() + 1);
			s--;
		}
		else if (s == 0)
		{
			break;
		}
	}*/
	m_currentTime = getCurrentTime();
	printf("second:%d\n", m_currentTime->tm_sec);
	printf("second:%d\n", m_currentTime->tm_min);
	printf("second:%d\n", m_currentTime->tm_hour);
	printf("second:%d\n", m_currentTime->tm_mday);
	printf("second:%d\n", m_currentTime->tm_mon);

	if (GameManager::getInstance()->getEnergy() < 30)
	{
		this->schedule(schedule_selector(TollgateScene::resumeEnergy), 60.0f);
		log("%d", GameManager::getInstance()->getEnergy());
	}
	

	// 设置时间
	if (GameManager::getInstance()->getIsGameOn() == false)		// 如果游戏还没有开始
	{
		TimeManager::getInstance()->setTime(INITIAL_TIME);
		GameManager::getInstance()->setIsGameOn(true);			// set game is on
		m_timeText->setText(StringUtils::format("%05.2f", TimeManager::getInstance()->getTime()));		// 设置时间标签按照格式显示时间
		//addSecondsByCard(GameManager::getInstance()->getTollgateNum());
		setNextTollgate();		// 随机下一关
	}
	else
	{
		m_timeText->setText(StringUtils::format("%05.2f", TimeManager::getInstance()->getTime()));		// 设置时间标签按照格式显示时间
		m_timeBar->setPercent(TimeManager::getInstance()->getTime() / TimeManager::getInstance()->getPreTime() * 100.0f);		// 设置时间进度条进度

		if(GameManager::getInstance()->getIsWaitToAddChest())
		{
			//创建宝箱
//			int tollgateNum = GameManager::getInstance()->getTollgateNum();
			bool i = GameManager::getInstance()->getIsWaitToAddChest();
			m_tollgateNumLabel->setString(StringUtils::format("%d", GameManager::getInstance()->getTollgateNum() + 1));
			setChest();
		}

		// 防止每次进入TollgateScene都加2秒时间
		else if (GameManager::getInstance()->getIsWaitToAddTime())
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
	m_goOnBtn->addTouchEventListener(this, toucheventselector(TollgateScene::onGoOnBtnClicked));

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
	m_t11->addTouchEventListener(this, toucheventselector(TollgateScene::onItem11Clicked));
	m_t12->addTouchEventListener(this, toucheventselector(TollgateScene::onItem12Clicked));
	m_cardBtn->addTouchEventListener(this, toucheventselector(TollgateScene::onCardBtnClicked));
	

//	SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/MainMenu.mp3", true);
	SoundManager::getInstance()->playMenuMusic();

	return true;
}

void TollgateScene::addDiamond()
{
	int i = random(1, 9);
	m_jewelText->setText(StringUtils::format("%d", GameManager::getInstance()->getJewel()));
	GameManager::getInstance()->setJewel(GameManager::getInstance()->getJewel() + i);		
}																							
																							
void TollgateScene::addEnergy()
{
	int i = random(1, 9);
	m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
	GameManager::getInstance()->setEnergy(GameManager::getInstance()->getEnergy() + i);
}

void TollgateScene::addCard()
{

	DataManager::getInstance()->pushBackACard(m_rewardCard->getCardinfo(), 1);
	DataManager::getInstance()->saveCardData();
	Card* rewardCard = CardManager::getInstance()->CreateACardByTypeAndLevel(m_rewardCard->getCardinfo(), 1, 0);
//	CardManager::getInstance()->InsertACard(rewardCard);
	CardManager::getInstance()->SortCardMsg();
}

void TollgateScene::setChest()
{
	//创建宝箱及宝箱出场动作
	auto visibleSize = Director::getInstance()->getVisibleSize();
	m_chest_sprite = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("res/images/chest/chest1.png"));
	m_chest_sprite->setPosition(visibleSize.width / 2 + 50, visibleSize.height / 2);
	m_chest_sprite->setScale(0.65, 0.65);
	this->addChild(m_chest_sprite);

	JumpTo * jumpto = JumpTo::create(1.0, Vec2(visibleSize.width / 2, visibleSize.height / 2), 50, 2);
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
	addSecondsByCard(GameManager::getInstance()->getNextTollgate());
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
		// 下一关不与上一关类型一样
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
	}
	else
	{
		label = Label::createWithTTF(TOLLGATE_NAME[r], "fonts/msyh.ttf", 40);
	}
	
	//普通模式下的显示关卡名字
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

void TollgateScene::resumeEnergy(float dt)
{	
	if (GameManager::getInstance()->getEnergy() < 30){
		GameManager::getInstance()->setEnergy(GameManager::getInstance()->getEnergy() + 1);
		m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
	}
}

tm* TollgateScene::getCurrentTime()
{
	time_t t = time(NULL);
	tm* lt = localtime(&t);

	int year = lt->tm_year;
	int month = lt->tm_mon;

	int yday = lt->tm_yday;
	int mday = lt->tm_mday;
	int wday = lt->tm_wday;

	int h = lt->tm_hour;
	int m = lt->tm_min;
	int s = lt->tm_sec;

	return lt;
}

int TollgateScene::getTimeStamp()
{
	timeval tm;
	gettimeofday(&tm, NULL);
	log("stamp %ld",tm.tv_usec/1000 + tm.tv_sec*1000);
	log("stamo %ld",tm.tv_sec);
	return tm.tv_sec;
}

void TollgateScene::addSecondsByCard(int info)
{
	for (auto card : CardManager::getInstance()->getAllCards())
	{
		if (info == card->getCardinfo())
		{
			TimeManager::getInstance()->addTime(card->getCardLevel()*0.02f);
			m_timeText->setText(StringUtils::format("%05.2f", TimeManager::getInstance()->getTime()));		// 设置时间标签按照格式显示时间
			break;
		}
	}
}

//创建开箱子的动画
cocos2d::Animate* TollgateScene::createChestOpenAnimate()
{
	int iFrameNum = 2;
	SpriteFrame* frame = NULL;
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

//这里设置继续按钮和关闭宝箱系统
void TollgateScene::onGoOnBtnClicked(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		if (m_chest_sprite)
		{
			m_chest_sprite->stopAllActions();
			m_chest_sprite->removeFromParent();
		}
		m_anotherChestText->setVisible(false);
		if (m_res)		// 如果res=true，则说明箭头在上面
		{
			m_goOnBtn->runAction(MoveBy::create(0.5, Point(0, -120)));
			m_cardBtn->runAction(MoveBy::create(0.5, Point(0, 120)));
		}
		m_res = false;  // 切换状态，卡片来到上面
		setNextTollgate();
		TimeManager::getInstance()->addTime(2.0f);				// add 2 seconds
		m_timeText->setText(StringUtils::format("%05.2f", TimeManager::getInstance()->getTime()));		// 设置时间标签按照格式显示时间
		m_timeBar->setPercent(100);
		GameManager::getInstance()->setIsWaitToAddChest(false);

		// 防止每次进入TollgateScene都加2秒时间
		/*if (GameManager::getInstance()->getIsWaitToAddTime())
		{
			addSeconds();
			CCLOG("added 2 seconds.");
			GameManager::getInstance()->setIsWaitToAddTime(false);
		}
		else
			showNextTollgate();*/
	}
}

void TollgateScene::onHomeBtnClicked(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::MainScene);
	}	
	GameManager::getInstance()->setIsWaitToAddChest(false);   //设置回主界面之后，再次进入时不显示宝箱
}

void TollgateScene::onCardBtnClicked(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		m_cardControlLayer = CardControlLayer::create();
		this->addChild(m_cardControlLayer);
	}
}

void TollgateScene::onTollgateLabelClicked(Ref* pSender)
{
	int nextTollgate = GameManager::getInstance()->getNextTollgate();
	int num = GameManager::getInstance()->getTollgateNum();
	if (num % 10 == 0 && GameManager::getInstance()->getEnergy() > 0)
	{
		GameManager::getInstance()->setEnergy(GameManager::getInstance()->getEnergy() - 1);
		m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
		SceneManager::getInstance()->changeScene((SceneManager::SceneType)(100 + num / 10));
	}
	else 
	{
		GameManager::getInstance()->setTollgate(nextTollgate);
		CCLOG("Tollgate %d change scene...", nextTollgate);
		int diff = GameManager::getInstance()->getDiff();
		int loop = GameManager::getInstance()->getLoop();
		if (GameManager::getInstance()->getEnergy() > 0)
		{
			GameManager::getInstance()->setEnergy(GameManager::getInstance()->getEnergy() - 1);
			m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
			SceneManager::getInstance()->changeScene((SceneManager::TollgateSceneType)nextTollgate, diff, loop);
		}
	}
}

void TollgateScene::onItem1Clicked(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED && GameManager::getInstance()->getEnergy() > 0)
	{
		log("tollgate 1");
		GameManager::getInstance()->setEnergy(GameManager::getInstance()->getEnergy() - 1);
		m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::DoubleTapScene, 0, 3);
	}
}

void TollgateScene::onItem2Clicked(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED && GameManager::getInstance()->getEnergy() > 0)
	{
		log("tollgate 2");
		GameManager::getInstance()->setEnergy(GameManager::getInstance()->getEnergy() - 1);
		m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::SlideCutScene, 0, 2);

	}
}

void TollgateScene::onItem3Clicked(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED && GameManager::getInstance()->getEnergy() > 0)
	{
		log("tollgate 3");
		GameManager::getInstance()->setEnergy(GameManager::getInstance()->getEnergy() - 1);
		m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::EatFlowersScene, 0, 1);
	}
}

void TollgateScene::onItem4Clicked(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED && GameManager::getInstance()->getEnergy() > 0)
	{
		log("tollgate 4");
		GameManager::getInstance()->setEnergy(GameManager::getInstance()->getEnergy() - 1);
		m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::BurrowAndAttackScene, 0, 2);
	}
}

void TollgateScene::onItem5Clicked(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED && GameManager::getInstance()->getEnergy() > 0)
	{
		log("tollgate 5");
		GameManager::getInstance()->setEnergy(GameManager::getInstance()->getEnergy() - 1);
		m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::JumpingOnPoolScene, 1, 2);
	}
}

void TollgateScene::onItem6Clicked(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED && GameManager::getInstance()->getEnergy() > 0)
	{
		log("tollgate 6");
		GameManager::getInstance()->setEnergy(GameManager::getInstance()->getEnergy() - 1);
		m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::ClassifyUnits, 1, 2);
	}
}

void TollgateScene::onItem7Clicked(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED && GameManager::getInstance()->getEnergy() > 0)
	{
		log("tollgate 7");
		GameManager::getInstance()->setEnergy(GameManager::getInstance()->getEnergy() - 1);
		m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::BOSS1);
	}
}

void TollgateScene::onItem8Clicked(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED && GameManager::getInstance()->getEnergy() > 0)
	{
		log("tollgate 8");
		GameManager::getInstance()->setEnergy(GameManager::getInstance()->getEnergy() - 1);
		m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::BOSS2);
	}
}

void TollgateScene::onItem9Clicked(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED && GameManager::getInstance()->getEnergy() > 0)
	{
		log("tollgate 9");
		GameManager::getInstance()->setEnergy(GameManager::getInstance()->getEnergy() - 1);
		m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
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
	this->addChild(m_flash);

	DelayTime* dt = DelayTime::create(1.5f);
	Hide* hideAction = Hide::create();
	ScaleTo* scaleto2 = ScaleTo::create(0.3, 0.000001);

	if (m_chest_sprite)
	{
		if ((m_chest_sprite->getBoundingBox().containsPoint(pos)) && (m_act != true) && (GameManager::getInstance()->getJewel() >= m_money))
		{
			GameManager::getInstance()->setJewel(GameManager::getInstance()->getJewel() - m_money);
			m_jewelText->setText(StringUtils::format("%d", GameManager::getInstance()->getJewel()));
			if (m_res)			// 如果当前是箭头在上面
			{/*
<<<<<<< HEAD
				GameManager::getInstance()->setJewel(GameManager::getInstance()->getJewel() - m_money);
				m_jewelText->setText(StringUtils::format("%d", GameManager::getInstance()->getJewel()));
				if (m_res)//如果当前是箭头在上面
				{
					m_goOnBtn->runAction(MoveBy::create(0.5, Point(0, -120)));
					m_cardBtn->runAction(MoveBy::create(0.5, Point(0, 120)));
					m_res = false;
				}
				//打开宝箱时触发鼓励文字
				if (m_act != true)
				{
					Label *m_label = Label::create("  GREATE!  ", "fonts/AveriaSansLibre-Bold.ttf", 40);
					m_label->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 135);
					this->addChild(m_label, 1, 2);
				}

				if (m_act != true)
				{
					m_flash->setVisible(true);
					m_flash->runAction(RotateTo::create(2, 100));
					m_flash->runAction(ScaleBy::create(1.8, 1.8));
					m_chest_sprite->runAction(m_createAnimate());
					m_chest_sprite->runAction(Sequence::create(DelayTime::create(2.3), scaleto2, hideAction, dt, NULL));
					m_flash->runAction(Sequence::create(DelayTime::create(2.3), hideAction, dt, NULL));
				}
				m_act = true;
				int i = random(1, 3);
				//int i = 3;
				if (i == Energy)
				{
					m++;
					//创建能量
					m_energy_sprite = Sprite::create("res/images/chest/Energy.png");
					m_energy_sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
					m_energy_sprite->setScale(0.01, 0.01);
					addChild(m_energy_sprite);
				}

				//能量提取
				else if (i == Jewel)
				{
					m++;
					//创建宝石
					m_diamond_sprite = Sprite::create("res/images/chest/Gem.png");
					m_diamond_sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
					m_diamond_sprite->setScale(0.01, 0.01);  //0.48是原设置的大小。想法：可以把sprite 变小，这样就按不到了
					addChild(m_diamond_sprite);
				}

				//卡片创建
				else if (i == Card)
				{
					m++;
					GameManager::getInstance()->setcardType(random(1, 10));
					//m_card_sprite = CardManager::getInstance()->CreateACardByTypeAndLevel((Card::CardInfo)(GameManager::getInstance()->getcardType()), 1,n);
					m_card_sprite = Card::createByLevelAndInfo(1, Card::CardInfo(GameManager::getInstance()->getcardType()));
					//按道理，这里的setPosition需要遍历CardVec，找到对应种类的卡片，排在最后
					m_card_sprite->setPosition(visibleSize.width / 2 - 40, visibleSize.height / 2 - 40);
					m_card_sprite->setScale(0.01, 0.01);
					this->addChild(m_card_sprite);
				}
=======*/
				m_goOnBtn->runAction(MoveBy::create(0.5, Point(0, -120)));
				m_cardBtn->runAction(MoveBy::create(0.5, Point(0, 120)));
				m_res = false;
			}
			// 打开宝箱时触发鼓励文字
			if (m_act != true)
			{
				Label* m_label = Label::create("  GREATE!  ", "fonts/AveriaSansLibre-Bold.ttf", 40);
				m_label->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 135);
				this->addChild(m_label, 1, 2);
//>>>>>>> 1b9834acc10b619a4b8d9f8477c599dcbcaa3cb5
			}

			if (m_act != true)
			{
				m_flash->setVisible(true);
				m_flash->runAction(RotateTo::create(2, 100));
				m_flash->runAction(ScaleBy::create(1.8, 1.8));
				m_chest_sprite->runAction(createChestOpenAnimate());
				m_chest_sprite->runAction(Sequence::create(DelayTime::create(2.3), scaleto2, hideAction, dt, NULL));
				m_flash->runAction(Sequence::create(DelayTime::create(2.3), hideAction, dt, NULL));
			}
			m_act = true;
			//int i = random(1, 2);
			int rewardType = 3;
			if (rewardType == REWARD_ENERGY)
			{
				m_chestOpenTimes++;
				//创建能量
				m_energy_sprite = Sprite::create("res/images/chest/Energy.png");
				m_energy_sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
				m_energy_sprite->setScale(0, 0);
				addChild(m_energy_sprite);
			}

			//能量提取
			else if (rewardType == REWARD_JEWEL)
			{
				m_chestOpenTimes++;
				//创建宝石
				m_diamond_sprite = Sprite::create("res/images/chest/Gem.png");
				m_diamond_sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
				m_diamond_sprite->setScale(0, 0); //0.48是原设置的大小。想法：可以把sprite 变小，这样就按不到了
				addChild(m_diamond_sprite);
			}

			//卡片创建
			else if (rewardType == REWARD_CARD)
			{
				m_chestOpenTimes++;

				int cardType = random(1, TOTAL_TOLLGATE_TYPE + TOTAL_BOSS_TYPE);
				m_rewardCard = Card::createByLevelAndInfo(1, cardType);
				m_rewardCard->setPosition(visibleSize.width / 2 - 40, visibleSize.height / 2 - 40);
				m_rewardCard->setScale(0, 0);
				this->addChild(m_rewardCard);
			}
		}
	}

	if (m_diamond_sprite)
	{
		m_diamond_sprite->runAction(Sequence::create(DelayTime::create(2.5f),
		                                             ScaleTo::create(0.5, 0.48),
		                                             NULL
		));
		if (m_diamond_sprite->getBoundingBox().containsPoint(pos))
		{
			runDiamond();
		}
	}
	if (m_energy_sprite)
	{
		m_energy_sprite->runAction(Sequence::create(DelayTime::create(2.5f),
		                                            ScaleTo::create(0.5, 0.48),
		                                            NULL
		));
		if (m_energy_sprite->getBoundingBox().containsPoint(pos))
		{
			runEnergy();
		}
	}
	else if (m_rewardCard)
	{
		m_rewardCard->runAction(Sequence::create(
			DelayTime::create(2.5f),
		    ScaleTo::create(0.5, 1.2),
		    NULL
		));
		if (m_rewardCard->getBoundingBox().containsPoint(pos))
		{
			runCard();
		}
	}
}

bool TollgateScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	return true;
}

void TollgateScene::onItem10Clicked(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED && GameManager::getInstance()->getEnergy() > 0)
	{
		log("tollgate 10");
		GameManager::getInstance()->setEnergy(GameManager::getInstance()->getEnergy() - 1);
		m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::FeedSnacks, 0, 2);
	}
}

void TollgateScene::onItem11Clicked(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED && GameManager::getInstance()->getEnergy() > 0)
	{
		log("tollgate 11");
		GameManager::getInstance()->setEnergy(GameManager::getInstance()->getEnergy() - 1);
		m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::fitthecircle, 0, 2);
	}
}

void TollgateScene::onItem12Clicked(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED && GameManager::getInstance()->getEnergy() > 0)
	{
		log("tollgate 12");
		GameManager::getInstance()->setEnergy(GameManager::getInstance()->getEnergy() - 1);
		m_energyText->setText(StringUtils::format("%d", GameManager::getInstance()->getEnergy()));
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::Runrunrun, 0, 2);
	}
}