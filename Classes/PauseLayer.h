// PauseLayer.h
/*
	暂停层，吞并触摸事件
*/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class PauseLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(PauseLayer);

	virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event *unused_event);

	void onResumeBtnClick(Ref *, cocos2d::ui::TouchEventType type);		// 恢复按钮点击事件
private:
	cocos2d::ui::Button * m_resumeBtn;
};