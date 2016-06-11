// DoubleTapScene.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <vector>
#include "Zergling.h"
#include "TollgateControlLayer.h"
const int GRID_ROW = 3;				// 设定默认的行数和列数
const int GRID_COL = 6;
const int GRID_WIDTH = 120;			// 小狗方块的宽度(和高度)
const int LEFT_MARGIN = 120;		// 小狗矩阵距离左边的距离
const int BOTTOM_MARGIN = 80;		// 小狗矩阵距离底部的距离

class DoubleTapGrid;

/*
	定死的狗狗矩阵
	0表示空，1-7表示狗的颜色
*/
static const int m_g[15][GRID_ROW][GRID_COL] =
{
	// easy
	{
		{ 0,3,0,0,3,0 },
		{ 0,4,0,0,4,0 },
		{ 0,6,0,0,6,0 }
	},
	{
		{ 5,0,0,0,0,5 },
		{ 3,5,7,5,7,3 },
		{ 7,0,0,0,0,7 }
	},
	{
		{ 0,5,2,2,5,0 },
		{ 0,5,2,2,5,0 },
		{ 0,5,2,2,5,0 }
	},
	{
		{ 0,3,0,0,4,2 },
		{ 0,7,0,0,7,0 },
		{ 2,4,0,0,3,0 }
	},
	{
		{ 0,3,7,6,4,0 },
		{ 0,0,0,0,0,0 },
		{ 0,7,3,4,6,0 }
	},
	// medium
	{
		{ 5,6,0,0,1,5 },
		{ 3,3,7,5,3,3 },
		{ 7,1,0,0,6,7 }
	},
	{
		{ 0,0,0,5,2,3 },
		{ 4,0,0,6,0,0 },
		{ 5,3,2,4,0,0 }
	},
	{
		{ 0,6,7,2,6,0 },
		{ 0,4,0,0,4,0 },
		{ 2,3,0,0,3,7 }
	},
	{
		{ 3,0,0,5,0,7 },
		{ 3,7,0,0,3,7 },
		{ 3,0,5,0,0,7 }
	},
	{
		{ 7,5,0,0,5,7 },
		{ 1,4,0,0,4,1 },
		{ 7,2,0,0,2,7 }
	},
	// hard
	{
		{ 4,3,1,6,1,7 },
		{ 7,3,6,6,3,7 },
		{ 7,1,6,1,3,4 }
	},
	{
		{ 3,1,1,1,1,3 },
		{ 7,5,5,5,5,7 },
		{ 3,1,1,1,1,3 }
	},
	{
		{ 7,5,4,6,5,7 },
		{ 1,4,3,3,4,1 },
		{ 7,2,6,4,2,7 }
	},
	{
		{ 1,0,0,5,6,1 },
		{ 1,5,2,2,4,1 },
		{ 1,0,6,4,0,1 }
	},
	{
		{ 1,6,7,2,6,1 },
		{ 1,4,1,1,4,1 },
		{ 2,3,0,0,3,7 }
	},
};

class DoubleTapScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);	// 根据难度和轮次数初始化一个关卡
	static cocos2d::Layer * create(int diff, int loop);

private:
//	void tollgateClear(cocos2d::EventCustom *);				// tollgate clear
//	void tollgateFail(cocos2d::EventCustom *);				// game over

	void newLevel(int diff);				// 根据难度创建一个新的轮次
	virtual void update();					// 主要用于刷新时间

private:
	TollgateControlLayer * m_controlLayer;
	DoubleTapGrid * m_grid;

};

class DoubleTapGrid : public cocos2d::Layer
{
public:
	static DoubleTapGrid * create(int diff, int loop, int row = GRID_ROW, int col = GRID_COL);		// 根据行列创建布局
	bool init(int diff, int loop, int row = GRID_ROW, int col = GRID_COL);

	// 根据网格坐标设置小狗的具体像素坐标
	void setZerglingPixPos(Zergling* zergling, int x, int y);

	// 根据颜色和网格坐标创建一个小狗，并且加入到渲染节点
	Zergling * createAZergling(Zergling::ZerglingColor color, int x, int y);

	virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	
private:
	int m_row, m_col;
	int m_loop, m_diff;
	bool m_isRunning;
	std::vector<std::vector<Zergling*>> m_zerglingGrid;

private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);		// 将像素坐标转化成格子矩阵中的坐标
	void generateNewZerglingGrid(const int diff);
	int getLivingZerglingsNum();			// 得到活的狗的数量
};