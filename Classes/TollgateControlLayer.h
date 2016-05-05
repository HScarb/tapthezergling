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

	virtual void update(float dt) override;

	void initTimeBar();		// �ڹؿ�����ʱ������ʱ����Ϊ��ǰʣ��ʱ��

	void tollgateClear(cocos2d::EventCustom *);	// tollgate clear callback
	void tollgateFail(cocos2d::EventCustom *);	// tollgate fail callback, at this time, game over
private:
	void onPauseBtnClick(Ref *, cocos2d::ui::TouchEventType type);

private:
	cocos2d::ui::Text * m_timeText;
	cocos2d::ui::LoadingBar * m_timeBar;
	cocos2d::ui::Button * m_pauseBtn;

};
