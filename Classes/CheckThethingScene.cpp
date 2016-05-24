//CheckThething.cpp
#include "CheckThething.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TimeManager.h"
#include "TollgateControlLayer.h"

USING_NS_CC;

using namespace std;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

Scene* CheckThething::createScene(int diff, int loop)
{
	auto scene = Scene::create();
	auto layer = CheckThething::create(diff, loop);
	scene->addChild(layer);
	return scene;
}