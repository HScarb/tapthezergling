// GameManager.h
/*
	游戏管理器
	- 保存和记录当前关卡、下一关的类型
	- 记录当前的分数
	- 
*/
#pragma once
#include "cocos2d.h"

class GameManager : public cocos2d::Node
{
public:
	static GameManager * getInstance();
	virtual bool init() override;

	CC_SYNTHESIZE(int, m_tollgate, Tollgate);			// 当前关卡类型
	CC_SYNTHESIZE(int, m_nextTollgate, NextTollgate);	// 下一关类型
	CC_SYNTHESIZE(int, m_score, Score);					// 当前分数
	CC_SYNTHESIZE(int, m_tollgateNum, TollgateNum);		// 当前关卡序号
	CC_SYNTHESIZE(int, m_jewel, Jewel);					// 当前的宝石数量
	CC_SYNTHESIZE(int, m_energy, Energy);				// 当前的能量数量
	CC_SYNTHESIZE(int, m_diff, Diff);					// 当前难度
	CC_SYNTHESIZE(int, m_loop, Loop);					// 当前关循环次数
	CC_SYNTHESIZE(bool, m_isGameOn, IsGameOn);			// 游戏是否已经开始
	CC_SYNTHESIZE(bool, m_isWaitToAddTime, IsWaitToAddTime);// 是否在等增加时间(关卡胜利之后增加2秒时间在此判断)

private:
	static GameManager * m_gameManager;

};