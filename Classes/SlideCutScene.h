//SlideCutScene
#ifndef _SlideCutScene_H_
#define _SlideCutScene_H_

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <vector>
#include "Farmer.h"
const int Grid_ROW = 6;				// �趨Ĭ�ϵ�����������
const int Grid_COL = 10;
const int Grid_WIDTH = 70;			// С������Ŀ��(�͸߶�)
const int Left_MARGIN = 130;		// С�����������ߵľ���
const int Bottom_MARGIN = 70;		// С���������ײ��ľ���

using namespace cocos2d;

class SlideCutGrid;
class IntMatrix;
/*
�����Ĺ�������
0��ʾ�գ�1��ʾ���ĳ���
*/
static const int m_a[1][Grid_ROW][Grid_COL] =
{
	// easy
	{
		{ 1, 0, 0, 0, 0, 1 ,1, 0, 1, 1},
		{ 1, 0, 0, 0, 1, 1 ,0, 1, 1, 1},
		{ 1, 0, 1, 1, 0, 1 ,0, 1, 1, 1},
		{ 1, 0, 1, 0, 0, 1 ,0, 1, 1, 1},
		{ 1, 1, 1, 1, 1, 1 ,0, 1, 1, 1},
		{ 1, 0, 0, 0, 0, 1 ,1, 0, 1, 1}
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
};

class SlideCutGrid :public Layer
{
public:
	static SlideCutGrid * create(int diff, int loop, int row = Grid_ROW, int col = Grid_COL);		// �������д�������
	bool init(int diff, int loop, int row = Grid_ROW, int col = Grid_COL);

	// ����������������С���ľ�����������
	void setFarmerPixPos(Farmer* farmer, int x, int y);

	// �����������괴��һ��С�������Ҽ��뵽��Ⱦ�ڵ�
	Farmer * createAFarmer(Farmer::Farmerappear appear, int x, int y);

	virtual bool SlideCutGrid::onTouchBegan(Touch *touch, Event *unused_event);
	virtual void SlideCutGrid::onTouchMoved(Touch *touch, Event *unused_event);
	virtual void SlideCutGrid::onTouchEnded(Touch *touch, Event *unused_event);
private:
	int m_row, m_col;
	int m_loop;
	bool m_isRunning;
	cocos2d::Label * m_touchesLabel;
	std::vector<std::vector<Farmer*>> m_farmerGrid;

private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);		// ����������ת���ɸ��Ӿ����е�����

};
#endif