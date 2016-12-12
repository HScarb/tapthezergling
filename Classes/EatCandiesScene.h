//EatCandiesScene.h
#ifndef EATCANDIESSCENE_H
#define EATCANDIESSCENE_H
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <vector>
#include "Flower.h"
#include "TollgateControlLayer.h"

const int grid_ROW = 9;				// �趨Ĭ�ϵ�����������
const int grid_COL = 9;
const int grid_WIDTH = 120;			// ����Ŀ��(�͸߶�)
const int left_MARGIN = 120;		// ���������ߵľ���
const int bottom_MARGIN = 80;		// �������ײ��ľ���

class EatCandiesGrid;
class IntMatrix;

class EatCandiesScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);	// �����ѶȺ��ִ�����ʼ��һ���ؿ�
	static cocos2d::Layer * create(int diff, int loop);

private:
	EatCandiesGrid * m_grid;
	TollgateControlLayer * m_controlLayer;

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

	// ���������������û��ľ�����������
	void setZerglingPixPos(Flower* zergling, int x, int y);

	// ������ɫ���������괴���������Ҽ��뵽��Ⱦ�ڵ�
	Flower * createflower(int color, int x, int y);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	int m_row, m_col;
	int m_loop, m_diff;
	bool m_isRunning;

	std::vector<std::vector<Flower*>> m_flowersesGrid;

private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);		// ����������ת���ɸ��Ӿ����е�����
	int getLivingFlowersNum();
	void generateNewZerglingGrid(const int diff);
};

#endif