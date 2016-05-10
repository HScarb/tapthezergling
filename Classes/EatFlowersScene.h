//EatFlowersScene.h
#ifndef EATFLOWERSSCENE_H
#define EATFLOWERSSCENE_H
#pragma once
#include "cocos2d.h"
#include <vector>
#include "Flower.h"
#include "TollgateControlLayer.h"

const int grid_ROW = 3;				// 默认的行数
const int grid_COL = 6;				// 默认的列数
const int grid_WIDTH = 80;			// 方块的宽度(和高度)
const int left_MARGIN = 120;		// 矩阵距离左边的距离
const int bottom_MARGIN = 80;		// 矩阵距离底部的距离

class EatFlowersGrid;
class IntMatrix;


static const int n_g[3][grid_ROW][grid_COL] =
{
	 //easy
	{
		{ 0, 1, 0, 0, 3, 0 },
		{ 0, 0, 0, 4, 0, 0 },
		{ 0, 0, 2, 0, 0, 0 }
	}
	//
	//
};

class EatFlowersScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);	
	static Layer * create(int diff, int loop);

private:
	void newLevel(int diff);				
	virtual void update();					

private:
	EatFlowersGrid * m_grid;
	TollgateControlLayer * m_controlLayer;
};

class EatFlowersGrid : public cocos2d::Layer
{
public:
	static EatFlowersGrid * create(int diff, int loop, int row = grid_ROW, int col = grid_COL);		// 根据行列创建布局
	bool init(int diff, int loop, int row = grid_ROW, int col = grid_COL);

	void setZerglingPixPos(Flower* zergling, int x, int y);

	Flower * createflower(Flower::FlowerColor color, int x, int y);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	int m_row, m_col;
	int m_loop, m_diff;
	bool m_isRunning;
	cocos2d::Label * m_touchesLabel;
	std::vector<std::vector<Flower*>> m_flowersesGrid;

private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);		// 将像素坐标转化成格子矩阵中的坐标
	int getLivingFlowersNum();
};

#endif