// TollgateControlLayer.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"

class TollgateControlLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init() override;
	CREATE_FUNC(TollgateControlLayer);

	void menuItem1Callback(cocos2d::Ref * pSender);
	void menuItem2Callback(cocos2d::Ref * pSender);

private:
	void onPauseBtnClick(Ref *, cocos2d::ui::TouchEventType type);

	virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event);
	virtual void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unused_event);
private:
	cocos2d::ui::Text * m_timeText;
	cocos2d::ui::LoadingBar * m_timeBar;
	cocos2d::ui::Button * m_pauseBtn;

	cocos2d::Vector<cocos2d::MenuItem*> _items;
};
