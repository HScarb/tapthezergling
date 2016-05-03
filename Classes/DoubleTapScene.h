// DoubleTapScene.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <vector>
#include "Zergling.h"
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
	virtual bool init(int diff, int loop);	// �����ѶȺ��ִ�����ʼ��һ���ؿ�
	static cocos2d::Layer * create(int diff, int loop);

private:
	void newLevel(int diff);				// �����Ѷȴ���һ���µ��ִ�
	virtual void update();					// ��Ҫ����ˢ��ʱ��

private:
	cocos2d::Node * m_controlLayer;
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
	cocos2d::Label * m_touchesLabel;
	std::vector<std::vector<Zergling*>> m_zerglingGrid;

private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);		// ����������ת���ɸ��Ӿ����е�����
	void generateNewZerglingGrid(const int diff);
	int getLivingZerglingsNum();			// �õ���Ĺ�������
};