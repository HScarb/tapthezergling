// JumpingOnPool.h
#pragma once
#include "cocos2d.h"
#include "TollgateControlLayer.h"
const int INTERVAL = 80;		// ÿ�еļ��
const float SCALE[] = { 1.0,0.84,0.68,0.52,0.36 };
/*
	
	ԭ������ 480, 400
	
*/
class Pool : public cocos2d::Sprite
{
public:
	Pool() { m_row = -1, m_dir = -1, m_isEnd = false; }
	static Pool * create(bool isEnd);
	cocos2d::Vec2 convertToPos();	// �������ڵ������ͷ�λ������ʵ������

private:
	CC_SYNTHESIZE(int, m_row, Row);		// ���ڵ�����,��0��ʼ,ԽСԽ����
	CC_SYNTHESIZE(int, m_dir, Dir);		// ���ڵķ�λ,0��1��
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
	void addAGroupOfPools(int diff);		// ����һ��(һ��loop)��pool
	void movePools();			// �ƶ�һ��

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

