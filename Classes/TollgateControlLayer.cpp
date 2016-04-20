// TollgateControlLayer.cpp
#include "TollgateControlLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

bool TollgateControlLayer::init()
{
	if (!Layer::init())
		return false;

	auto UI = CSLoader::createNode("TollgateControlLayer.csb");
	addChild(UI);

	m_pauseBtn = (Button*)(UI->getChildByName("Button_pause"));
	m_timeBar = (LoadingBar*)(UI->getChildByName("LoadingBar_time"));
	m_timeText = (Text*)(UI->getChildByName("Text_time"));
	

	m_pauseBtn->addTouchEventListener(this, toucheventselector(TollgateControlLayer::onPauseBtnClick));
	return true;
}

void TollgateControlLayer::onPauseBtnClick(Ref*, cocos2d::ui::TouchEventType type)
{
	switch(type)
	{
	case TOUCH_EVENT_BEGAN: 
		log("tapped");
		break;
	case TOUCH_EVENT_MOVED: break;
	case TOUCH_EVENT_ENDED: break;
	case TOUCH_EVENT_CANCELED: break;
	default: break;
	}
}