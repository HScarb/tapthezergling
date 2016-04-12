// DoubleTapScene.h
#pragma once
#include "cocos2d.h"
#include "filters/cocos2dFilters.h"
#include "VisibleRect.h"

class DoubleTapScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);	// 根据难度和轮次数初始化一个关卡
	static cocos2d::Layer * create(int diff, int loop);

private:
	void newLevel(int diff);				// 根据难度创建一个新的轮次
};