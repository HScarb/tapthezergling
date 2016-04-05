// TemplateScene.cpp
#include "TemplateScene.h"
USING_NS_CC;

Scene* TemplateScene::createScene(int diff, int loop)
{
	auto scene = Scene::create();
	auto layer = TemplateScene::create(diff, loop);
	scene->addChild(layer);
	return scene;
}

bool TemplateScene::init(int diff, int loop)
{
	if (!Layer::init())
		return false;

	auto sp = Sprite::create("zergling_big_1.png");
	
	auto x = random(1, 5);
	log("%d", x);
	auto y = random(5, 10);
	log("%d", y);
	100 * CCRANDOM_0_1();		// Ëæ»úÊý
	sp->setPosition(x,y);

	this->addChild(sp);

	return true;
}

cocos2d::Layer* TemplateScene::create(int diff, int loop)
{
	auto pRef = new TemplateScene();
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