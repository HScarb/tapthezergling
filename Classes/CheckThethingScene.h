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
const int X_MARGIN = 380;	//x��ı߾�
const int Y_MARGIN = 100;	//y��ı߾�

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
	static CheckThethingGrid * create(int diff, int loop, int row = hang, int col = lie);		// �������д�������
	bool init(int diff, int loop, int row = hang, int col = lie);

	// ����������������С���ľ�����������
	void setZerglingPixPos(farmerandflower* farmerandflower, int x, int y);

	// �����������괴��һ��С�������Ҽ��뵽��Ⱦ�ڵ�
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
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);		// ����������ת���ɸ��Ӿ����е�����
	int getLivingSamplesNum();									// �õ����ũ�������
	void generateNewThingGrid(const int diff);					// �����µĵ�λ����
};