//CheckThethingScene.h
#ifndef CHECKTHETHINGSCENE_H
#define CHECKTHETHINGSCENE_H
#pragma once

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "farmerandflower.h"
#include "TollgateControlLayer.h"
#include <vector>

const int hang = 12;
const int lie = 12;
const int width = 80;
const int l_margin = 300;
const int b_margin = 120;

class CheckThethingGrid;
class IntMatrix;

static const int c_g[6][hang][lie] =
{
	//��ʱ����
	{
		{ 1, 2, 3 },
		{ 1, 0, 0 },
		{ 0, 4, 0 }
	},
};

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
	static CheckThethingGrid * create(int diff, int loop, int row = hang, int col = lie);		// �������д�������
	bool init(int diff, int loop, int row = hang, int col = lie);

	// ����������������С���ľ�����������
	void setZerglingPixPos(farmerandflower* farmerandflower, int x, int y);

	// �����������괴��һ��С�������Ҽ��뵽��Ⱦ�ڵ�
	farmerandflower * createflower(int type, int x, int y);

	//void setSamplePixPos(Farmerandflower * farmerandflower, int y);
	//Farmerandflower * sampleAppear(int type, int y);


	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	int m_row, m_col;
	int m_loop, m_diff;
	bool m_isRunning;
	cocos2d::Label * m_touchesLabel;
	//std::vector<Farmerandflower*> m_farmerandflowerGrid;
	std::vector<std::vector<farmerandflower*>> m_thingGrid;

private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);		// ����������ת���ɸ��Ӿ����е�����
	int getLivingFarmersNum();			// �õ����ũ�������
	void generateNewZerglingGrid(const int diff);
};


#endif
