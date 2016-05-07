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

	CC_SYNTHESIZE(int, m_tollgate, Tollgate);			// ��ǰ�ؿ�����
	CC_SYNTHESIZE(int, m_nextTollgate, NextTollgate);	// ��һ������
	CC_SYNTHESIZE(int, m_score, Score);					// ��ǰ����
	CC_SYNTHESIZE(int, m_tollgateNum, TollgateNum);		// ��ǰ�ؿ����
	CC_SYNTHESIZE(int, m_jewel, Jewel);					// ��ǰ�ı�ʯ����
	CC_SYNTHESIZE(int, m_energy, Energy);				// ��ǰ����������
	CC_SYNTHESIZE(bool, m_isGameOn, IsGameOn);			// ��Ϸ�Ƿ��Ѿ���ʼ

private:
	static GameManager * m_gameManager;

};