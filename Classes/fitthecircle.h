//fitthecircle.h
#pragma once
#include "cocos2d.h"
#include "TollgateControlLayer.h"
#include "FilterSprite.h"
const int ROW = 3;
const int COL = 6;
const int WIDTH = 120;
const int L_MARGIN = 120;
const int B_MARGIN = 80;

class fitthecircleGrid;

static const int j_g[1][3][6] =
{
	{
		{ 0, 3, 7, 0 ,8, 4},
		{ 0, 0, 0, 0, 0, 0},
		{ 0, 1, 5, 0, 6, 2}
	},
};

class Circle : public FilterSprite
{
public:
	enum CircleType
	{
		NONE = 0,
		RED = 1,
		ORANGE,
		YELLOW,
		GREEN,
		g1,
		g2,
		g3,
		g4
	};

	static Circle * createByColor(CircleType color = NONE);
	bool init(int color);
	void tapped();

	CC_SYNTHESIZE(int, m_colorType, ColorType);
};

class fitthecircleScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	bool init(int diff, int loop);
	static cocos2d::Layer * create(int diff, int loop);

	void speedup();		//加快旋转速度

private:
	cocos2d::ui::Button * m_pauseBtn;
	cocos2d::ui::Text * m_timeText;
	cocos2d::ui::LoadingBar * m_timeBar;

	TollgateControlLayer * m_controlLayer;
	fitthecircleGrid * m_grid;
};

class fitthecircleGrid : public cocos2d::Layer
{
public:
	static fitthecircleGrid * create(int diff, int loop,int row = ROW, int col = COL);
	bool init(int diff, int loop,int row = ROW,int col = COL);

	void setCirclePixPos(Circle* circle, int x, int y);

	Circle * createCircle(Circle::CircleType color, int x, int y);

	int getCircle();

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	int m_row, m_col;
	int m_loop, m_diff;
	bool m_isRunning;
	std::vector<std::vector<Circle*>> m_spriteGrid;

private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);		// 将像素坐标转化成格子矩阵中的坐标
	void generateGrid(const int diff);
};

