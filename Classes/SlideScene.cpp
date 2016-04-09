//SlideScene
#include"SlideScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace cocos2d;

Scene* SlideScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SlideScene::create();
	scene->addChild(layer);
	return scene;
}

bool SlideScene::init()
{
	if (!Layer::init())
		return false;
	int i;
	for (i = 0; i < diff; i++)
	{
		auto sp = Sprite::create("SCs_Zergling_C3_02.png");
		auto x = random(100,300);
		log("%d", x);
		auto y = random(100, 300);
		log("%d", y);		// Ëæ»úÊý
		sp->setPosition(x, y);

		this->addChild(sp);
	}
}