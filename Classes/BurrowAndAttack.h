#ifndef _FeedZerglingScene_H_
#define _FeedZerglingScene_H_


#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <vector>
#include"Food.h"
#include"Zergling.h"
#include "TollgateControlLayer.h"
const int GRID_Row = 3;				// 设定默认的行数和列数
const int GRID_Col = 6;
const int GRID_Width = 120;			// 小狗方块的宽度(和高度)
const int LEFT_Margin = 120;		// 小狗矩阵距离左边的距离
const int BOTTOM_Margin = 80;		// 小狗矩阵距离底部的距离

class FeedZerglingGrid;

/*
定死的狗狗矩阵
0表示空，1-7表示狗的颜色
*/
static const int m_f[4][GRID_Row][GRID_Col] =
{
	// easy
	{
		{ 1, 0, 2, 0, 0, 1 },
		{ 3, 2, 0, 0, 0, 0 },
		{ 0, 0, 0, 3, 1, 0 }
	}
	// medium
	// hard
};

class FeedZerglingScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);	// 根据难度和轮次数初始化一个关卡
	static cocos2d::Layer * create(int diff, int loop);

private:
	void tollgateClear(cocos2d::EventCustom *);				// tollgate clear
	void tollgateFail(cocos2d::EventCustom *);				// game over

	void newLevel(int diff);				// 根据难度创建一个新的轮次
	virtual void update();					// 主要用于刷新时间

private:
	TollgateControlLayer * m_controlLayer;
	FeedZerglingGrid * m_grid;
};

class FeedZerglingGrid : public cocos2d::Layer
{
public:
	static FeedZerglingGrid * create(int diff, int loop, int row = GRID_Row, int col = GRID_Col);		// 根据行列创建布局
	bool init(int diff, int loop, int row = GRID_Row, int col = GRID_Col);

	// 根据网格坐标设置小狗的具体像素坐标
	void setFoodPixPos(Food* food, int x, int y);

	// 根据颜色和网格坐标创建一个小狗，并且加入到渲染节点
	Food * createTFood(Food::Foodtype color, int x, int y);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	int m_row, m_col;
	int m_loop, m_diff;
	bool m_isRunning;
	cocos2d::Label * m_touchesLabel;
	std::vector<std::vector<Food*>> m_foodGrid;
	cocos2d::MotionStreak* streak; // 拖尾
	cocos2d::Sprite* m_zergling;
private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);		// 将像素坐标转化成格子矩阵中的坐标
	void generateVisualizationFoodGrid(const int diff);
	int getVisualizationFoodNum();			// 得到活的狗的数量
};

#endif