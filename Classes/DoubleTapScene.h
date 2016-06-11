// DoubleTapScene.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <vector>
#include "Zergling.h"
#include "TollgateControlLayer.h"
const int GRID_ROW = 3;				// �趨Ĭ�ϵ�����������
const int GRID_COL = 6;
const int GRID_WIDTH = 120;			// С������Ŀ��(�͸߶�)
const int LEFT_MARGIN = 120;		// С�����������ߵľ���
const int BOTTOM_MARGIN = 80;		// С���������ײ��ľ���

class DoubleTapGrid;

/*
	�����Ĺ�������
	0��ʾ�գ�1-7��ʾ������ɫ
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
	virtual bool init(int diff, int loop);	// �����ѶȺ��ִ�����ʼ��һ���ؿ�
	static cocos2d::Layer * create(int diff, int loop);

private:
//	void tollgateClear(cocos2d::EventCustom *);				// tollgate clear
//	void tollgateFail(cocos2d::EventCustom *);				// game over

	void newLevel(int diff);				// �����Ѷȴ���һ���µ��ִ�
	virtual void update();					// ��Ҫ����ˢ��ʱ��

private:
	TollgateControlLayer * m_controlLayer;
	DoubleTapGrid * m_grid;

};

class DoubleTapGrid : public cocos2d::Layer
{
public:
	static DoubleTapGrid * create(int diff, int loop, int row = GRID_ROW, int col = GRID_COL);		// �������д�������
	bool init(int diff, int loop, int row = GRID_ROW, int col = GRID_COL);

	// ����������������С���ľ�����������
	void setZerglingPixPos(Zergling* zergling, int x, int y);

	// ������ɫ���������괴��һ��С�������Ҽ��뵽��Ⱦ�ڵ�
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
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);		// ����������ת���ɸ��Ӿ����е�����
	void generateNewZerglingGrid(const int diff);
	int getLivingZerglingsNum();			// �õ���Ĺ�������
};