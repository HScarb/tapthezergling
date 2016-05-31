//CheckThethingScene.h
#ifndef CHECKTHETHINGSCENE_H
#define CHECKTHETHINGSCENE_H
#pragma once

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "farmerandflower.h"
#include "TollgateControlLayer.h"

class Farmerandflower;
const int hang = 6;
const int lie = 6;
const int width = 200;
const int l_margin = 200;
const int b_margin = 100;

class CheckThethingGrid;
class IntMatrix;

static const int c_g[3][hang][lie] =
{
	{
		{ 1, 2, 3 },
		{ 1, 0, 0 },
		{ 0, 4, 0 },
		{ 0, 0, 2 }
	},
};

class CheckThethingScene : public cocos2d::Layer
{
	public:
		static cocos2d::Scene * createScene(int diff, int loop);
		virtual bool init(int diff, int loop);
		static cocos2d::Layer * create(int diff, int loop);

	private:
		void newLevel(int diff);
		virtual void update();

	private:
		CheckThethingGrid * m_grid;
		TollgateControlLayer * m_controlLayer;

	private:
	cocos2d::ui::Button * m_pauseBtn;
	cocos2d::ui::Text * m_timeText;
	cocos2d::ui::LoadingBar * m_timeBar;
};

class CheckThethingGrid : public cocos2d::Layer
{
public:
	static CheckThethingGrid * create(int diff, int loop, int row = hang, int col = lie);		// 根据行列创建布局
	bool init(int diff, int loop, int row = hang, int col = lie);

	// 根据网格坐标设置小狗的具体像素坐标
	void setFarmerPixPos(Farmerandflower* farmerandflower, int x, int y);

	// 根据网格坐标创建一个小狗，并且加入到渲染节点
	Farmerandflower * farmerandflowerAppear(int type, int x, int y);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	int m_row, m_col;
	int m_loop, m_diff;
	bool m_isRunning;
	cocos2d::Label * m_touchesLabel;
	std::vector<std::vector<Farmerandflower*>> m_farmerandflowerGrid;

private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);		// 将像素坐标转化成格子矩阵中的坐标
	void generateNewFarmersGrid(const int diff);
	int getLivingFarmersNum();			// 得到活的农民的数量
};


#endif
