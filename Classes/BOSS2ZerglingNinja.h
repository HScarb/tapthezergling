// BOSS2ZerglingNinja.h
#pragma once
#include "cocos2d.h"
#include "TollgateControlLayer.h"
#include "ui\CocosGUI.h"

class BOSS2ZerglingNinja : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	CREATE_FUNC(BOSS2ZerglingNinja);
	virtual bool init() override;

	virtual bool onTouchBegan(cocos2d::Touch * pTouch, cocos2d::Event * pEvent);

private:
	struct Pt
	{
		Pt(){}
		Pt(cocos2d::Vec2 pos, int num)
		{
			this->pos = pos;
			this->num = num;
		}
		bool operator==(Pt p)
		{
			return this->num == p.num;
		}
		cocos2d::Vec2 pos;
		int num;
	};

	Pt m_curPt;			// 目前所在的位置
	bool m_isRunning;
	TollgateControlLayer * m_controlLayer;
	std::vector<Pt> m_posVector;
	cocos2d::Sprite * m_woods[9];
	cocos2d::Sprite * m_zerglingNinja;

};