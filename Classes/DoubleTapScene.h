// DoubleTapScene.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <vector>

class Zergling;
class DoubleTapGrid;

class DoubleTapScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);	// 根据难度和轮次数初始化一个关卡
	static cocos2d::Layer * create(int diff, int loop);

	virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);

private:
	void newLevel(int diff);				// 根据难度创建一个新的轮次

private:
	DoubleTapGrid * m_grid;

private:
	cocos2d::ui::Button * m_pauseBtn;
	cocos2d::ui::Text * m_timeText;
	cocos2d::ui::LoadingBar * m_timeBar;
};

class DoubleTapGrid : public cocos2d::Node
{
public:
private:
	std::vector<std::vector<Zergling*>> m_zerglingGrid;

};