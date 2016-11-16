// NoTouchLayer.h
#ifndef __NO_TOUCH_LAYER_H__
#define __NO_TOUCH_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class NoTouchLayer : public Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(NoTouchLayer);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
};

#endif
