// DoubleTapScene.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <vector>
#include "Zergling.h"
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
static const int m_g[9][GRID_ROW][GRID_COL] =
{
	// easy
	{
		{ 5,0,0,0,0,5 },
		{ 3,5,7,5,7,3 },
		{ 7,0,0,0,0,7 }
	}
	// medium
	// hard
};

class DoubleTapScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);	// 根据难度和轮次数初始化一个关卡
	static cocos2d::Layer * create(int diff, int loop);

private:
	void newLevel(int diff);				// 根据难度创建一个新的轮次
	virtual void update();					// 主要用于刷新时间

private:
	cocos2d::Node * m_controlLayer;
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
	cocos2d::Label * m_touchesLabel;
	std::vector<std::vector<Zergling*>> m_zerglingGrid;

private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);		// 将像素坐标转化成格子矩阵中的坐标
	void generateNewZerglingGrid(const int diff);
	int getLivingZerglingsNum();			// 得到活的狗的数量
};