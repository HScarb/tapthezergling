// TemplateScene.h
#pragma once
#include "cocos2d.h"

class TemplateScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);
	static cocos2d::Layer * create(int diff, int loop);

};