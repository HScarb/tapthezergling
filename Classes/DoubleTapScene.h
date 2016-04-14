// DoubleTapScene.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <vector>
#include "Zergling.h"
const int GRID_ROW = 3;		// 设定默认的行数和列数
const int GRID_COL = 6;
const int GRID_WIDTH = 120;

class DoubleTapGrid;
class IntMatrix;

static const int m_g[9][GRID_ROW][GRID_COL] =
{
	// easy
	{
		{ 1,2,3,4,5,6 },
		{ 1,2,3,4,5,6 },
		{ 1,2,3,4,5,6 }
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
	DoubleTapGrid * m_grid;

private:
	cocos2d::ui::Button * m_pauseBtn;
	cocos2d::ui::Text * m_timeText;
	cocos2d::ui::LoadingBar * m_timeBar;
};

class DoubleTapGrid : public cocos2d::Node
{
public:
	static DoubleTapGrid * create(int diff, int loop, int row = GRID_ROW, int col = GRID_COL);		// 根据行列创建布局
	bool init(int diff, int loop, int row = GRID_ROW, int col = GRID_COL);

	// 根据网格坐标设置小狗的具体像素坐标
	void setZerglingPixPos(Zergling* zergling, int x, int y);

	// 根据颜色和网格坐标创建一个小狗，并且加入到渲染节点
	Zergling * createAZergling(Zergling::ZerglingColor color, int x, int y);

	virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);

private:
	int m_row, m_col;
	int m_loop;
	bool m_isRunning;
	std::vector<std::vector<Zergling*>> m_zerglingGrid;

};