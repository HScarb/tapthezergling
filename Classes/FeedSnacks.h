//FeedSnacks.h
#ifndef _FeedSnacksScene_H_
#define _FeedSnacksScene_H_
#include "cocos2d.h"
#include "TollgateControlLayer.h"
#include <vector>

const int GRID_ROw = 3;				// �趨Ĭ�ϵ�����������
const int GRID_COl = 6;
const int GRID_WIDTh = 120;			// С������Ŀ��(�͸߶�)
const int LEFT_MARGIn = 120;		// С�����������ߵľ���
const int BOTTOM_MARGIn = 80;		// С���������ײ��ľ���


class FeedSnacksGrid;
class IntMatrix;

class Snack : public cocos2d::Sprite
{
public:
	typedef enum
	{
		NONE = 0,
		SCV = 1,
		Drone = 2,
		Probe,
		FRED,
		FYELLOW,
		FBLUE,
		RED,
		ORANGE,
		YELLOW,
		GREEN,
		CYAN,
		BLUE,
		PURPLE,
	} SnackType;
	static Snack * create(SnackType type);
	bool initWithType(SnackType type);


	CC_SYNTHESIZE(int, m_row, Row);
	CC_SYNTHESIZE(SnackType, m_type, Type);
};
class FeedSnacks : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);
	static cocos2d::Layer * create(int diff, int loop);

private:
	virtual void update();
	TollgateControlLayer * m_controlLayer;
	FeedSnacksGrid * m_grid;
	
};
class FeedSnacksGrid :public cocos2d::Layer
{
public:
	static FeedSnacksGrid* create(int diff, int loop, int row = GRID_ROw, int col = GRID_COl);
	bool init(int diff, int loop, int row = GRID_ROw, int col = GRID_COl);

	// ����������������ũ��ľ�����������
	void SetSnackPixPos(Snack* worker, int x, int y);

	// ������Ҫ������Snack
	Snack * createATSnack();
	//�Ƴ�Ч��
	void Remove();

	virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);

private:
	int m_row, m_col;
	int m_diff, m_loop;
	bool m_isRunning;
	int m_counter=0;
	Snack::SnackType m_Type, m_temp;
	std::vector<std::vector<Snack*>> m_snackVector;
private:
	cocos2d::Vec2 convertToGridPos(cocos2d::Vec2 pixPos);// ����������ת���ɸ��Ӿ����е�����
	void generateNewSnacksGrid(const int diff);
	int getLivingAtypeSnackNum();			// �õ����ũ�������
	int getLivingAllSnackNum();
	// building
	cocos2d::Sprite * m_SnacktempBase;
};
#endif