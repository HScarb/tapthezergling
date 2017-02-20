// DataManager
/*
	用来管理和存储用户的游戏信息
	- 时间
	- 分数
	- 宝石
	- 能量
	- 卡片
	- 等等
*/
#pragma once
#include "cocos2d.h"

struct CardData
{
	int info;		// 卡片类型
	int level;		// 卡片等级
	int num;		// 该类型等级卡片的数量
};

class DataManager : public cocos2d::Node
{
public:
	static DataManager * getInstance();
	virtual bool init() override;

	void saveData();
	void loadData();

	void initCardData();

	CC_SYNTHESIZE(int, m_bestScore, BestScore);
	CC_SYNTHESIZE(int, m_jewel, Jewel);
	CC_SYNTHESIZE(int, m_energy, Energy);
	CC_SYNTHESIZE(int, m_lastLoginDate, LastLoginDate);
	CC_SYNTHESIZE(int, m_startCollectionTime, StartTimeStamp);
	CC_SYNTHESIZE(int, m_endCollectionTime, EndingTimeStamp);
	CC_SYNTHESIZE(tm*, m_startDate, StartDate);

	CC_SYNTHESIZE(std::string, _cardDataPath, CardDataPath);				// 卡片数据存放路径
	CC_SYNTHESIZE(std::vector<CardData*>, m_cardData, CardData);			// 用vector存储卡片数据
private:
	static DataManager * m_dataManager;

};
