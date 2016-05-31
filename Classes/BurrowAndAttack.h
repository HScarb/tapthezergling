//BurrowAndAttackScene.h
#ifndef _BurrowAndAttackScene_H_
#define _BurrowAndAttackScene_H_

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <vector>
#include "Worker.h"
#include "TollgateControlLayer.h"
const int GRID_Row = 3;				// �趨Ĭ�ϵ�����������
const int GRID_Col = 6;
const int GRID_Width = 120;			// С������Ŀ��(�͸߶�)
const int LEFT_Margin = 120;		// С�����������ߵľ���
const int BOTTOM_Margin = 80;		// С���������ײ��ľ���

class BurrowAndAttackGrid;
class IntMatrix;
/*
�����Ĺ�������
0��ʾ�գ�1��ʾ���ĳ���
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

	// ����������������ũ��ľ�����������
	void SetWorkerPixPos(Worker* worker,int x,int y);

	// �����������괴��һ��ũ�񣬲��Ҽ��뵽��Ⱦ�ڵ�
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
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);// ����������ת���ɸ��Ӿ����е�����
	void generateNewWorkerGrid(const int diff);
	int getLivingWorkerNum();			// �õ����ũ�������
};

#endif