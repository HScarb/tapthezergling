//EatFlowersScene.h
#ifndef EATFLOWERSSCENE_H
#define EATFLOWERSSCENE_H
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "Flower.h"
#include "TollgateControlLayer.h"

USING_NS_CC;

class EatFlowersScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);	
	static cocos2d::Layer * create(int diff, int loop);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);

private:
	int m_loop, m_diff;
	bool m_isRunning;

	TollgateControlLayer * m_controlLayer;

	int place;
	int is_occupy[15];
	cocos2d::ui::Button * m_pauseBtn;
	cocos2d::ui::Text * m_timeText;
	cocos2d::ui::LoadingBar * m_timeBar;
	cocos2d::Sprite * m_flower;
	std::vector<cocos2d::Vec2>  m_Vec2Vec;			//���15�����꣬�������������У���������λ�õĴ���
	cocos2d::Vector<cocos2d::Sprite*> m_flowerVec;								//���3�仨
};
#endif