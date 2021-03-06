// LoadingScene.cpp
#include "LoadingScene.h"
#include "SimpleAudioEngine.h"
#include "AnimationUtil.h"
#include "SceneManager.h"
#include "DataManager.h"
#include "Global.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace CocosDenshion;

const int TOTAL_TEXTURE_NUM = 248;	// 12 + small zerglings(137) + 3 workers + 15 RESOURCE + 4 bases + 10 smallUnitDeath + 7 other units + 10 Cards + 4 runner-dog + 4 flowers= 196

Scene* LoadingScene::createScene() 
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingScene::init()
{
	if (!Layer::init())
		return false;


	m_texture_num = 0;		// 当前已加载图片置零
	m_total_time = 0.0;
	int *ptexture_num = &m_texture_num;

	// 创建"Loading"标签
	auto winSize = Director::getInstance()->getWinSize();
	auto label = Label::create("Loading...", "Arial", 50);
	//auto label = Label::createWithTTF("Loading...", "fonts/AveriaSansLibre-Bold", 36);
	label->setTextColor(Color4B::WHITE);
	label->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(label);

	auto addTextureCallback = [ptexture_num](Texture2D* texture)
	{
		(*ptexture_num)++;
		log("loaded a texture async, now num = %d", *ptexture_num);
	};

	// 异步加载图片
	for (int i = 1; i <= 4; i++)
	{
		TextureCache::getInstance()->addImageAsync(StringUtils::format("res/Res/flower_%d.png", i),addTextureCallback);
	}
	for (int i = 1; i <= 4; i++)
	{
		TextureCache::getInstance()->addImageAsync(StringUtils::format("res/Res/ZerlingAnimation/r_%d.png", i), addTextureCallback);
	}
	for (int i = 1; i <= 2; i++)
	{
		TextureCache::getInstance()->addImageAsync(StringUtils::format("res/images/chest/chest%d.png", i), addTextureCallback);
	}
	for (int i = 1; i <= 4;i++)
	{
		TextureCache::getInstance()->addImageAsync(StringUtils::format("zergling_big_%d.png", i), addTextureCallback);
	}
	for (int i = 0; i <= 7;i++)
	{
		TextureCache::getInstance()->addImageAsync(StringUtils::format("zergling_small_%d.png", i), addTextureCallback);
	}
	// small zerglings, 137 pics
	for (int i = 1; i <= 137;i++)
	{
		TextureCache::getInstance()->addImageAsync(StringUtils::format("zergling/SCs_Zergling_C3_%02d.png", i), addTextureCallback);
	}
	// Death animation 10
	for (int i = 1; i <= 10;i++)
	{
		TextureCache::getInstance()->addImageAsync(StringUtils::format("star crafts/starcrafts_SmallUnit_Death_%d.png", i), addTextureCallback);
	}
	// workers 3
	TextureCache::getInstance()->addImageAsync(PATH_SCV_SMALL, addTextureCallback);
	TextureCache::getInstance()->addImageAsync(PATH_DRONE_SMALL, addTextureCallback);
	TextureCache::getInstance()->addImageAsync(PATH_PROBE_SMALL, addTextureCallback);
	// other units 7
	TextureCache::getInstance()->addImageAsync(PATH_MARINE_SMALL, addTextureCallback);
	TextureCache::getInstance()->addImageAsync(PATH_MARAUDER_SMALL, addTextureCallback);
	TextureCache::getInstance()->addImageAsync(PATH_ZERGLING_SMALL, addTextureCallback);
	TextureCache::getInstance()->addImageAsync(PATH_OVERLORD_SMALL, addTextureCallback);
	TextureCache::getInstance()->addImageAsync(PATH_ROACH_SMALL, addTextureCallback);
	TextureCache::getInstance()->addImageAsync(PATH_ZEALOT_SMALL, addTextureCallback);
	TextureCache::getInstance()->addImageAsync(PATH_STALKER_SMALL, addTextureCallback);
	// RESOURCE 15
	TextureCache::getInstance()->addImageAsync(StringUtils::format("RESOURCE/add_two.png"), addTextureCallback);
	TextureCache::getInstance()->addImageAsync(StringUtils::format("RESOURCE/button_accept_1.png"), addTextureCallback);
	TextureCache::getInstance()->addImageAsync(StringUtils::format("RESOURCE/button_accept_2.png"), addTextureCallback);
	TextureCache::getInstance()->addImageAsync(StringUtils::format("RESOURCE/button_play_1.png"), addTextureCallback);
	TextureCache::getInstance()->addImageAsync(StringUtils::format("RESOURCE/button_play_2.png"), addTextureCallback);
	TextureCache::getInstance()->addImageAsync(StringUtils::format("RESOURCE/button_x_1.png"), addTextureCallback);
	TextureCache::getInstance()->addImageAsync(StringUtils::format("RESOURCE/button_x_2.png"), addTextureCallback);
	TextureCache::getInstance()->addImageAsync(StringUtils::format("RESOURCE/button-cards-1.png"), addTextureCallback);
	TextureCache::getInstance()->addImageAsync(StringUtils::format("RESOURCE/button-cards-2.png"), addTextureCallback);
	TextureCache::getInstance()->addImageAsync(StringUtils::format("RESOURCE/button-home-1.png"), addTextureCallback);
	TextureCache::getInstance()->addImageAsync(StringUtils::format("RESOURCE/button-home-2.png"), addTextureCallback);
	TextureCache::getInstance()->addImageAsync(StringUtils::format("RESOURCE/button-pause-1.png"), addTextureCallback);
	TextureCache::getInstance()->addImageAsync(StringUtils::format("RESOURCE/button-pause-2.png"), addTextureCallback);
	TextureCache::getInstance()->addImageAsync(StringUtils::format("RESOURCE/button-setting-1.png"), addTextureCallback);
	TextureCache::getInstance()->addImageAsync(StringUtils::format("RESOURCE/button-setting-2.png"), addTextureCallback);
	// Bases 4
	TextureCache::getInstance()->addImageAsync(PATH_TERRAN_BASE, addTextureCallback);
	TextureCache::getInstance()->addImageAsync(PATH_ZERG_BASE, addTextureCallback);
	TextureCache::getInstance()->addImageAsync(PATH_PROTOSS_BASE, addTextureCallback);
	TextureCache::getInstance()->addImageAsync(PATH_SPAWNINGPOOL, addTextureCallback);
	//Cards
	for (int i = 1; i <= 5; i++)
	{
		TextureCache::getInstance()->addImageAsync(StringUtils::format("Cards/Card_BOSS1_%d.jpg", i), addTextureCallback);
		TextureCache::getInstance()->addImageAsync(StringUtils::format("Cards/Card_BOSS2_%d.jpg", i), addTextureCallback);
		TextureCache::getInstance()->addImageAsync(StringUtils::format("Cards/Card_BurrowAndAttack_%d.jpg", i), addTextureCallback);
		TextureCache::getInstance()->addImageAsync(StringUtils::format("Cards/Card_CheckTheThing_%d.jpg", i), addTextureCallback);
		TextureCache::getInstance()->addImageAsync(StringUtils::format("Cards/Card_ClassifyUnits_%d.jpg", i), addTextureCallback);
		TextureCache::getInstance()->addImageAsync(StringUtils::format("Cards/Card_DoubleTap_%d.jpg", i), addTextureCallback);
		TextureCache::getInstance()->addImageAsync(StringUtils::format("Cards/Card_EatFlowers_%d.jpg", i), addTextureCallback);
		TextureCache::getInstance()->addImageAsync(StringUtils::format("Cards/Card_JumpingOnPool_%d.jpg", i), addTextureCallback);
		TextureCache::getInstance()->addImageAsync(StringUtils::format("Cards/Card_FeadSnacks_%d.jpg", i), addTextureCallback);
		TextureCache::getInstance()->addImageAsync(StringUtils::format("Cards/Card_SlideCut_%d.jpg", i), addTextureCallback);
	}

	// 开启加载进度检测
	schedule(schedule_selector(LoadingScene::onTextureLoading));

	// 预加载音效
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/MainMenu.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/Back2.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/Back3.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Sounds/1.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/boom.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/buttonclick.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/chomp.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/dao.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/grassstep.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/kernelpult.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/losthead.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/plant.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/points.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/polevault.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/shoop.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/splat1.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/splat2.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/winmusic.mp3");

	// 加载用户记录
	DataManager::getInstance()->loadData();

	return true;
}

void LoadingScene::onTextureLoading(float dt)
{
	m_total_time += dt;
	if(m_texture_num == TOTAL_TEXTURE_NUM)
	{
		unschedule(schedule_selector(LoadingScene::onTextureLoading));
		log("load done! Total time used: %f", m_total_time);

		auto call = CallFunc::create([]()
		{
			SceneManager::getInstance()->changeScene(SceneManager::MainScene);
		});

		this->runAction(call);
		/*
		// 挂一只狗
		auto dog = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("zergling_big_1.png"));
		//auto dog = Sprite::create("zergling_big_1.png");
		dog->setScale(0.3, 0.3);
		dog->setPosition(480, 270);
		this->addChild(dog);
		*/
		/*
		// 挂一只会动的狗
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto dog = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("zergling_big_1.png"));
		dog->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		dog->setScale(0.3, 0.3);
		this->addChild(dog);
		Animation * animation = AnimationUtil::createWithFrameNameAndNum("zergling_big_", 4, 0.08f, -1, true);
		dog->runAction(Animate::create(animation));
		*/
	}
}
