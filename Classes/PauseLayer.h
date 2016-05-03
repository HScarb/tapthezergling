// PauseLayer.h
/*
	ÔÝÍ£²ã£¬ÍÌ²¢´¥ÃþÊÂ¼þ
*/
#pragma once
#include "cocos2d.h"

class PauseLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(PauseLayer);

	virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event *unused_event);
};