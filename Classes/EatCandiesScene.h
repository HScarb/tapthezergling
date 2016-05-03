//EatCandiesScene.h
#ifndef EATCANDIESSCENE_H
#define EATCANDIESSCENE_H

#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <vector>
//#include "Zergling.h"
#include "Flower.h"
/*
const int grid_row = 6;
const int grid_col = 6;

const int grid_width = 240;
const int left_margin = 120;
const int bottom_margin = 100;

class EatCandiesGrid;

static const int m_f[9][grid_row][grid_col] =
{
	// easy
	{
		{ 5, 0, 0, 0, 0, 5 },
		{ 3, 5, 7, 5, 7, 3 },
		{ 7, 0, 0, 0, 0, 7 }
	}
	// medium
	// hard
};


class EatCandiesScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);	// 根据难度和轮次数初始化一个关卡
	static cocos2d::Layer * create(int diff, int loop);

private:
	EatCandiesGrid *n_grid;
	//少void newLevel(int diff);				// 根据难度创建一个新的轮次
	//virtual void update();					// 主要用于刷新时间

private:
	cocos2d::ui::Button * m_pauseBtn;
	cocos2d::ui::Text * m_timeText;
	cocos2d::ui::LoadingBar * m_timeBar;

};

class EatCandiesGrid :public cocos2d::Layer
{
public:
	static  EatCandiesGrid* create(int diff, int loop, int row = grid_row, int col = grid_col);		// 根据行列创建布局
	bool init(int diff, int loop, int row = grid_row, int col = grid_col);

	// 根据网格坐标设置花的具体像素坐标
	void setFlower(Flower* flower, int x, int y);

	// 根据颜色和网格坐标创建花，并且加入到渲染节点
	Flower * createFlower(Flower::FlowerColor color, int x, int y);

	virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event) override;//单点触摸事件
	
private:
	int m_row, m_col;
	int m_loop;
	int m_isRunning;
	cocos2d::Label * n_touchesLable;
	std::vector<std::vector<Flower*>> m_flowerGrid;

private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);
};
*/


const int grid_ROW = 3;				// 设定默认的行数和列数
const int grid_COL = 6;
const int grid_WIDTH = 120;			// 小狗方块的宽度(和高度)
const int left_MARGIN = 120;		// 小狗矩阵距离左边的距离
const int bottom_MARGIN = 80;		// 小狗矩阵距离底部的距离

class EatCandiesGrid;
class IntMatrix;


static const int n_g[4][grid_ROW][grid_COL] =
{
	// easy
	{
		{ 0, 1, 0, 0, 3 },
		{ 0, 0, 0, 4, 0 },
		{ 0, 0, 2, 0, 0 }
	}
	// medium
	// hard
};

class EatCandiesScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);	// 根据难度和轮次数初始化一个关卡
	static cocos2d::Layer * create(int diff, int loop);


private:
	void newLevel(int diff);				// 根据难度创建一个新的轮次
	virtual void update();					// 主要用于刷新时间

private:
	EatCandiesGrid * m_grid;

private:
	cocos2d::ui::Button * m_pauseBtn;
	cocos2d::ui::Text * m_timeText;
	cocos2d::ui::LoadingBar * m_timeBar;
};

class EatCandiesGrid : public cocos2d::Layer
{
public:
	static EatCandiesGrid * create(int diff, int loop, int row = grid_ROW, int col = grid_COL);		// 根据行列创建布局
	bool init(int diff, int loop, int row = grid_ROW, int col = grid_COL);

	// 根据网格坐标设置小狗的具体像素坐标
	void setZerglingPixPos(Flower* zergling, int x, int y);

	// 根据颜色和网格坐标创建一个小狗，并且加入到渲染节点
	Flower * createflower(Flower::FlowerColor color, int x, int y);

	virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event) override;
	virtual void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event *unused_event);

private:
	int m_row, m_col;
	int m_loop;
	bool m_isRunning;
	cocos2d::Label * m_touchesLabel;
	std::vector<std::vector<Flower*>> m_flowersesGrid;

private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);		// 将像素坐标转化成格子矩阵中的坐标

};

#endif