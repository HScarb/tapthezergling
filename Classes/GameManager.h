// GameManager.h
/*
	��Ϸ������
	- ����ͼ�¼��ǰ�ؿ�����һ�ص�����
	- ��¼��ǰ�ķ���
	- 
*/
#pragma once
#include "cocos2d.h"

class GameManager : public cocos2d::Node
{
public:
	static GameManager * getInstance();
	virtual bool init() override;

	void setNextTollgate(int i);								// ������һ�صĹؿ�����
	int getNextTollgate();										// �����һ�صĹؿ�����

	void resetTollgateData();									// ����Ϸʧ�ܺ�����ؿ���Ϣ

protected:
	int m_nextTollgate;
	

	CC_SYNTHESIZE(int, m_tollgate, Tollgate);					// ��ǰ�ؿ�����
	CC_SYNTHESIZE(int, m_score, Score);						// ��ǰ����
	CC_SYNTHESIZE(int, m_tollgateNum, TollgateNum);			// ��ǰ�ؿ����
	CC_SYNTHESIZE(int, m_jewel, Jewel);						// ��ǰ�ı�ʯ����
	CC_SYNTHESIZE(int, m_energy, Energy);						// ��ǰ����������
	CC_SYNTHESIZE(int, m_diff, Diff);							// ��ǰ�Ѷ�
	CC_SYNTHESIZE(int, m_loop, Loop);							// ��ǰ��ѭ������
	CC_SYNTHESIZE(int, m_speed, speed);                       //fitthecircle�ص���ת�ٶ�
	CC_SYNTHESIZE(bool, m_isGameOn, IsGameOn);					// ��Ϸ�Ƿ��Ѿ���ʼ
	CC_SYNTHESIZE(bool, m_isWaitToAddTime, IsWaitToAddTime);	// �Ƿ��ڵ�����ʱ��(�ؿ�ʤ��֮������2��ʱ���ڴ��ж�)
	CC_SYNTHESIZE(bool, m_isWaitToAddChest, IsWaitToAddChest);	// �Ƿ��ڵ���ʾ����

private:
	static GameManager * m_gameManager;

};