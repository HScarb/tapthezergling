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

	m_scrollView = nullptr;
	m_t1 = nullptr;
	m_t2 = nullptr;
	m_t3 = nullptr;

	m_tollgateNumLabel = nullptr;

	// ����UI
	auto rootNode = CSLoader::createNode("TollgateScene.csb");
	addChild(rootNode);

	//���ؿ�Ƭ�ϳɲ�
	m_cardControlLayer = CardControlLayer::create();
	this->addChild(m_cardControlLayer, 11);
	m_cardControlLayer->setVisible(false);

	// tollgate Num label
	m_tollgateNumLabel = Label::createWithTTF(StringUtils::format("%d", GameManager::getInstance()->getTollgateNum()), "fonts/AveriaSansLibre-Bold.ttf", 50);
	m_tollgateNumLabel->setPosition(486, 70);
	this->addChild(m_tollgateNumLabel);

	// ��������
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
	
	/* !!!���ùؿ�Ŀ¼����ʾ�������Ե�ʱ���������Ϊ��ʾ */
	m_scrollView->setVisible(false);

	m_energyText->setText("0");
	m_jewelText->setText("0");
	m_energyBar->setPercent(10.0f);
	m_timeBar->setPercent(100.0f);
	m_timeText->setText("00.00");
	
	// ����ʱ��
	if (GameManager::getInstance()->getIsGameOn() == false)		// �����Ϸ��û�п�ʼ
	{
		TimeManager::getInstance()->setTime(INITIAL_TIME);
		GameManager::getInstance()->setIsGameOn(true);			// set game is on
		m_timeText->setText(StringUtils::format("%05.2f", TimeManager::getInstance()->getTime()));		// ����ʱ���ǩ���ո�ʽ��ʾʱ��

		setNextTollgate();		// �����һ��
	}
	else
	{
		m_timeText->setText(StringUtils::format("%05.2f", TimeManager::getInstance()->getTime()));		// ����ʱ���ǩ���ո�ʽ��ʾʱ��
		m_timeBar->setPercent(TimeManager::getInstance()->getTime() / TimeManager::getInstance()->getPreTime() * 100.0f);		// ����ʱ�����������

		if (GameManager::getInstance()->getIsWaitToAddTime())
		{
			addSeconds();
			CCLOG("added 2 seconds.");
			GameManager::getInstance()->setIsWaitToAddTime(false);
		}
		else
			showNextTollgate();
	}

	// ������������
	m_homeBtn->addTouchEventListener(this, toucheventselector(TollgateScene::onHomeBtnClicked));
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
		m_timeText->setText(StringUtils::format("%05.2f", TimeManager::getInstance()->getTime()));		// ����ʱ���ǩ���ո�ʽ��ʾʱ��
		m_timeBar->setPercent(100);
		setNextTollgate();
	});
	
	this->addChild(swooth);
	swooth->runAction(Sequence::create(delay0, big1, delay1, small1, callFunc1, big2, delay2, Spawn::createWithTwoActions(small2, moveBy), callFunc2, nullptr));
	
}

void TollgateScene::setNextTollgate()
{
	int r = 0;
	// �����һ�������֮ǰû�йؿ�
	if(GameManager::getInstance()->getTollgate() == 0)
	{
		r = random(2, TOTAL_TOLLGATE_TYPE);
		GameManager::getInstance()->setNextTollgate(r);
	}
	// ���֮ǰ�йؿ�
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
	// ��ʾ�ؿ����
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
		m_cardControlLayer->showLayer();
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
void TollgateScene::onItem10Clicked(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		log("tollgate 10");
		SceneManager::getInstance()->changeScene(SceneManager::TollgateSceneType::FeedSnacks, 0, 2);
	}
}