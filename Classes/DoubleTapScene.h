// DoubleTapScene.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <vector>
#include "Zergling.h"
const int GRID_ROW = 3;		// �趨Ĭ�ϵ�����������
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
	virtual bool init(int diff, int loop);	// �����ѶȺ��ִ�����ʼ��һ���ؿ�
	static cocos2d::Layer * create(int diff, int loop);

private:
	void newLevel(int diff);				// �����Ѷȴ���һ���µ��ִ�
	virtual void update();					// ��Ҫ����ˢ��ʱ��

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
	static DoubleTapGrid * create(int diff, int loop, int row = GRID_ROW, int col = GRID_COL);		// �������д�������
	bool init(int diff, int loop, int row = GRID_ROW, int col = GRID_COL);

	// ����������������С���ľ�����������
	void setZerglingPixPos(Zergling* zergling, int x, int y);

	// ������ɫ���������괴��һ��С�������Ҽ��뵽��Ⱦ�ڵ�
	Zergling * createAZergling(Zergling::ZerglingColor color, int x, int y);

	virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);

private:
	int m_row, m_col;
	int m_loop;
	bool m_isRunning;
	std::vector<std::vector<Zergling*>> m_zerglingGrid;

};