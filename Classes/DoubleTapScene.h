// DoubleTapScene.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"

class DoubleTapScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);	// �����ѶȺ��ִ�����ʼ��һ���ؿ�
	static cocos2d::Layer * create(int diff, int loop);

private:
	void newLevel(int diff);				// �����Ѷȴ���һ���µ��ִ�

private:
	cocos2d::ui::Button * m_pauseBtn;
	cocos2d::ui::Text * m_timeText;
	cocos2d::ui::LoadingBar * m_timeBar;
};