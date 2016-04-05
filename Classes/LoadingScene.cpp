// LoadingScene.cpp
#include "LoadingScene.h"
#include "SimpleAudioEngine.h"
#include "AnimationUtil.h"
#include "SceneManager.h"
USING_NS_CC;
using namespace CocosDenshion;
const int TOTAL_TEXTURE_NUM = 4;

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
	for (int i = 1; i <= 4;i++)
	{
		TextureCache::getInstance()->addImageAsync(StringUtils::format("zergling_big_%d.png", i), addTextureCallback);
	}

	// 开启加载进度检测
	schedule(schedule_selector(LoadingScene::onTextureLoading));
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
