//EatCandiesScene.h
#ifndef EATCANDIESSCENE_H
#define EATCANDIESSCENE_H

#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <vector>
//#include "Zergling.h"
#include "Flower.h"
/*
const int grid_row = 6;
const int grid_col = 6;

const int grid_width = 240;
const int left_margin = 120;
const int bottom_margin = 100;

class EatCandiesGrid;

static const int m_f[9][grid_row][grid_col] =
{
	// easy
	{
		{ 5, 0, 0, 0, 0, 5 },
		{ 3, 5, 7, 5, 7, 3 },
		{ 7, 0, 0, 0, 0, 7 }
	}
	// medium
	// hard
};


class EatCandiesScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);	// �����ѶȺ��ִ�����ʼ��һ���ؿ�
	static cocos2d::Layer * create(int diff, int loop);

private:
	EatCandiesGrid *n_grid;
	//��void newLevel(int diff);				// �����Ѷȴ���һ���µ��ִ�
	//virtual void update();					// ��Ҫ����ˢ��ʱ��

private:
	cocos2d::ui::Button * m_pauseBtn;
	cocos2d::ui::Text * m_timeText;
	cocos2d::ui::LoadingBar * m_timeBar;

};

class EatCandiesGrid :public cocos2d::Layer
{
public:
	static  EatCandiesGrid* create(int diff, int loop, int row = grid_row, int col = grid_col);		// �������д�������
	bool init(int diff, int loop, int row = grid_row, int col = grid_col);

	// ���������������û��ľ�����������
	void setFlower(Flower* flower, int x, int y);

	// ������ɫ���������괴���������Ҽ��뵽��Ⱦ�ڵ�
	Flower * createFlower(Flower::FlowerColor color, int x, int y);

	virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event) override;//���㴥���¼�
	
private:
	int m_row, m_col;
	int m_loop;
	int m_isRunning;
	cocos2d::Label * n_touchesLable;
	std::vector<std::vector<Flower*>> m_flowerGrid;

private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);
};
*/


const int grid_ROW = 3;				// �趨Ĭ�ϵ�����������
const int grid_COL = 6;
const int grid_WIDTH = 120;			// С������Ŀ��(�͸߶�)
const int left_MARGIN = 120;		// С�����������ߵľ���
const int bottom_MARGIN = 80;		// С���������ײ��ľ���

class EatCandiesGrid;
class IntMatrix;


static const int n_g[4][grid_ROW][grid_COL] =
{
	// easy
	{
		{ 0, 1, 0, 0, 3 },
		{ 0, 0, 0, 4, 0 },
		{ 0, 0, 2, 0, 0 }
	}
	// medium
	// hard
};

class EatCandiesScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);	// �����ѶȺ��ִ�����ʼ��һ���ؿ�
	static cocos2d::Layer * create(int diff, int loop);


private:
	void newLevel(int diff);				// �����Ѷȴ���һ���µ��ִ�
	virtual void update();					// ��Ҫ����ˢ��ʱ��

private:
	EatCandiesGrid * m_grid;

private:
	cocos2d::ui::Button * m_pauseBtn;
	cocos2d::ui::Text * m_timeText;
	cocos2d::ui::LoadingBar * m_timeBar;
};

class EatCandiesGrid : public cocos2d::Layer
{
public:
	static EatCandiesGrid * create(int diff, int loop, int row = grid_ROW, int col = grid_COL);		// �������д�������
	bool init(int diff, int loop, int row = grid_ROW, int col = grid_COL);

	// ����������������С���ľ�����������
	void setZerglingPixPos(Flower* zergling, int x, int y);

	// ������ɫ���������괴��һ��С�������Ҽ��뵽��Ⱦ�ڵ�
	Flower * createflower(Flower::FlowerColor color, int x, int y);

	virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event) override;
	virtual void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event *unused_event);

private:
	int m_row, m_col;
	int m_loop;
	bool m_isRunning;
	cocos2d::Label * m_touchesLabel;
	std::vector<std::vector<Flower*>> m_flowersesGrid;

private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);		// ����������ת���ɸ��Ӿ����е�����

};

#endif