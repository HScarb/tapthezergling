// ScoreScene.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"

class ScoreScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	CREATE_FUNC(ScoreScene);
	virtual bool init() override;

private:
	void onHomeBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onRestartBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);

private:
	// °´Å¥
	cocos2d::ui::Button * m_homeBtn;
	cocos2d::ui::Button * m_restartBtn;
	cocos2d::ui::Text * m_scoreText;
};
