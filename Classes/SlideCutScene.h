//SlideCutScene
#ifndef _SlideCutScene_H_
#define _SlideCutScene_H_

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <vector>
#include "Farmer.h"
#include "TollgateControlLayer.h"
const int Grid_ROW = 6;				// 设定默认的行数和列数
const int Grid_COL = 10;
const int Grid_WIDTH = 70;			// 小狗方块的宽度(和高度)
const int Left_MARGIN = 130;		// 小狗矩阵距离左边的距离
const int Bottom_MARGIN = 40;		// 小狗矩阵距离底部的距离

class SlideCutGrid;
class IntMatrix;
/*
定死的狗狗矩阵
0表示空，1表示狗的出现
*/
static const int m_a[1][Grid_ROW][Grid_COL] =
{
	// easy
	{
		{ 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0},
		{ 0, 0, 0, 0, 1, 1 ,0, 0, 0, 0},
		{ 0, 0, 0, 1, 1, 1 ,1, 0, 0, 0},
		{ 0, 0, 1, 0, 0, 0 ,0, 1, 0, 0},
		{ 0, 1, 0, 0, 0, 0 ,0, 0, 1, 0},
		{ 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0}
	}
	// medium
	// hard
};

class SlideCutScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);
	static Layer * create(int diff, int loop);

private:
	virtual void update();
private:
	SlideCutGrid * m_grid;
	TollgateControlLayer * m_controlLayer;
};

class SlideCutGrid :public cocos2d::Layer
{
public:
	static SlideCutGrid * create(int diff, int loop, int row = Grid_ROW, int col = Grid_COL);		// 根据行列创建布局
	bool init(int diff, int loop, int row = Grid_ROW, int col = Grid_COL);

	// 根据网格坐标设置小狗的具体像素坐标
	void setFarmerPixPos(Farmer* farmer, int x, int y);

	// 根据网格坐标创建一个小狗，并且加入到渲染节点
	Farmer * createAFarmer(int, int x, int y);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
private:
	int m_row, m_col;
	int m_loop, m_diff;
	bool m_isRunning;
	std::vector<std::vector<Farmer*>> m_farmerGrid;
	cocos2d::MotionStreak* streak; // 拖尾
private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);		// 将像素坐标转化成格子矩阵中的坐标
	void generateNewFarmersGrid(const int diff);
	int getLivingFarmersNum();			// 得到活的农民的数量

};
#endif