// JumpingOnPool.h
#pragma once
#include "cocos2d.h"
#include "TollgateControlLayer.h"
const int INTERVAL = 80;		// 每行的间隔
const float SCALE[] = { 1.0,0.84,0.68,0.52,0.36 };
/*
	
	原点坐标 480, 400
	
*/
class Pool : public cocos2d::Sprite
{
public:
	Pool() { m_row = -1, m_dir = -1, m_isEnd = false; }
	static Pool * create(bool isEnd);
	cocos2d::Vec2 convertToPos();	// 给定所在的行数和方位，计算实际坐标

private:
	CC_SYNTHESIZE(int, m_row, Row);		// 所在的行数,从0开始,越小越往下
	CC_SYNTHESIZE(int, m_dir, Dir);		// 所在的方位,0左1右
	CC_SYNTHESIZE(bool, m_isEnd, IsEnd);
	// right: y = -5x + 300
	// left: y = 5x + 300
};

class JumpingOnPoolScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	bool init(int diff, int loop);
	static cocos2d::Layer * create(int diff, int loop);

	void initPools(int diff, int loop);
	void addAGroupOfPools(int diff);		// 增加一组(一个loop)的pool
	void movePools();			// 移动一格

	virtual bool onTouchBegan(cocos2d::Touch * pTouch, cocos2d::Event * pEvent);
private:

private:
	int m_diff, m_loop;
	bool m_isRunning;
	cocos2d::Vector<Pool*> m_poolVector;
	cocos2d::Vector<Pool*> m_poolShowVector;
	cocos2d::Sprite * m_zergling;
	TollgateControlLayer * m_controlLayer;
};

