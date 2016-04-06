// TollgateScene.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"

class TollgateScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(TollgateScene);

private:
	// 标签和按钮和进度条

};