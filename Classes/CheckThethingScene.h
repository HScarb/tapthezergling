//CheckThethingScene.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "farmerandflower.h"
#include "TollgateControlLayer.h"
#include <vector>

const int hang = 3;
const int lie = 3;
const int CTT_GRID_WIDTH = 100;
const int X_MARGIN = 380;	//x轴的边距
const int Y_MARGIN = 100;	//y轴的边距

class CheckThethingGrid;

class CheckThethingScene : public cocos2d::Layer
{
	public:
		static cocos2d::Scene * createScene(int diff, int loop);
		virtual bool init(int diff, int loop);
		static cocos2d::Layer * create(int diff, int loop);

	private:
		void newLevel(int diff);
		virtual void update();

	private:
		CheckThethingGrid * m_grid;
		TollgateControlLayer * m_controlLayer;

	private:
	cocos2d::ui::Button * m_pauseBtn;
	cocos2d::ui::Text * m_timeText;
	cocos2d::ui::LoadingBar * m_timeBar;
};

class CheckThethingGrid : public cocos2d::Layer
{
public:
	static CheckThethingGrid * create(int diff, int loop, int row = hang, int col = lie);		// 根据行列创建布局
	bool init(int diff, int loop, int row = hang, int col = lie);

	// 根据网格坐标设置小狗的具体像素坐标
	void setZerglingPixPos(farmerandflower* farmerandflower, int x, int y);

	// 根据网格坐标创建一个小狗，并且加入到渲染节点
	farmerandflower * createUnit(int type, int x, int y);

	//void setSamplePixPos(Farmerandflower * farmerandflower, int y);
	//Farmerandflower * sampleAppear(int type, int y);


	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	int m_row, m_col;
	int m_loop, m_diff;
	bool m_isRunning;
	std::vector<std::vector<farmerandflower*>> m_thingGrid;
	std::vector<farmerandflower*> m_sampleGrid;
	
private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);		// 将像素坐标转化成格子矩阵中的坐标
	int getLivingSamplesNum();									// 得到活的农民的数量
	void generateNewThingGrid(const int diff);					// 创建新的单位矩阵
};