//BurrowAndAttackScene.h
#ifndef _BurrowAndAttackScene_H_
#define _BurrowAndAttackScene_H_

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <vector>
#include "Worker.h"
#include "TollgateControlLayer.h"
const int GRID_Row = 3;				// 设定默认的行数和列数
const int GRID_Col = 6;
const int GRID_Width = 120;			// 小狗方块的宽度(和高度)
const int LEFT_Margin = 120;		// 小狗矩阵距离左边的距离
const int BOTTOM_Margin = 80;		// 小狗矩阵距离底部的距离

class BurrowAndAttackGrid;
class IntMatrix;
/*
定死的狗狗矩阵
0表示空，1表示狗的出现
*/
static const int m_w[1][GRID_Row][GRID_Col] =
{
	// easy
	{
		{ 1, 0, 1, 0, 1, 0 },
		{ 0, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 0 }
	}
	// medium
	// hard
};

class BurrowAndAttackScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);
	static Layer * create(int diff, int loop);


private:
	virtual void update();
private:
	BurrowAndAttackGrid * m_grid;
	TollgateControlLayer * m_controlLayer;
};

class BurrowAndAttackGrid :public cocos2d::Layer
{
public:
	static BurrowAndAttackGrid* create(int diff, int loop, int row = GRID_Row, int col = GRID_Col);
	bool init(int diff, int loop, int row = GRID_Row, int col = GRID_Col);

	// 根据网格坐标设置农民的具体像素坐标
	void SetWorkerPixPos(Worker* worker,int x,int y);

	// 根据网格坐标创建一个农民，并且加入到渲染节点
	Worker * createAWorker(int, int x, int y);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	int m_row, m_col;
	int m_diff, m_loop;
	bool m_isRunning;
	cocos2d::Sprite *m_zergling;
	cocos2d::Vec2 m_delta, m_Bpos, m_Epos;
	std::vector<std::vector<Worker*>> m_workergrid;
private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);// 将像素坐标转化成格子矩阵中的坐标
	void generateNewWorkerGrid(const int diff);
	int getLivingWorkerNum();			// 得到活的农民的数量
};

#endif