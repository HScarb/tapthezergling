//SlideScene
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"

class SlideScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);
	static Layer * create(int diff, int loop);

private:
	
	
};