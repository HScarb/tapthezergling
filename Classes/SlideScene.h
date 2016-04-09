//SlideScene
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"

using namespace cocos2d;

class SlideScene : public cocos2d::Layer
{
public:
	static Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);
	static Layer * create(int diff, int loop);

private:
	
	
};