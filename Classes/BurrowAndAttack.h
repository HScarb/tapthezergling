#ifndef _FeedZerglingScene_H_
#define _FeedZerglingScene_H_


#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <vector>
#include"Food.h"
#include"Zergling.h"
#include "TollgateControlLayer.h"
const int GRID_Row = 3;				// �趨Ĭ�ϵ�����������
const int GRID_Col = 6;
const int GRID_Width = 120;			// С������Ŀ��(�͸߶�)
const int LEFT_Margin = 120;		// С�����������ߵľ���
const int BOTTOM_Margin = 80;		// С���������ײ��ľ���

class FeedZerglingGrid;

/*
�����Ĺ�������
0��ʾ�գ�1-7��ʾ������ɫ
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
	virtual bool init(int diff, int loop);	// �����ѶȺ��ִ�����ʼ��һ���ؿ�
	static cocos2d::Layer * create(int diff, int loop);

private:
	void tollgateClear(cocos2d::EventCustom *);				// tollgate clear
	void tollgateFail(cocos2d::EventCustom *);				// game over

	void newLevel(int diff);				// �����Ѷȴ���һ���µ��ִ�
	virtual void update();					// ��Ҫ����ˢ��ʱ��

private:
	TollgateControlLayer * m_controlLayer;
	FeedZerglingGrid * m_grid;
};

class FeedZerglingGrid : public cocos2d::Layer
{
public:
	static FeedZerglingGrid * create(int diff, int loop, int row = GRID_Row, int col = GRID_Col);		// �������д�������
	bool init(int diff, int loop, int row = GRID_Row, int col = GRID_Col);

	// ����������������С���ľ�����������
	void setFoodPixPos(Food* food, int x, int y);

	// ������ɫ���������괴��һ��С�������Ҽ��뵽��Ⱦ�ڵ�
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
	cocos2d::MotionStreak* streak; // ��β
	cocos2d::Sprite* m_zergling;
private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);		// ����������ת���ɸ��Ӿ����е�����
	void generateVisualizationFoodGrid(const int diff);
	int getVisualizationFoodNum();			// �õ���Ĺ�������
};

#endif