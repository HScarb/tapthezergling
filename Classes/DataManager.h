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

class DataManager : public cocos2d::Node
{
public:
	static DataManager * getInstance();
	virtual bool init() override;

	void saveData();
	void loadData();

	CC_SYNTHESIZE(int, m_bestScore, BestScore);
	CC_SYNTHESIZE(int, m_jewel, Jewel);
	CC_SYNTHESIZE(int, m_energy, Energy);
	CC_SYNTHESIZE(int, m_startCollectionTime, StartTimeStamp);
	CC_SYNTHESIZE(int, m_endCollectionTime, EndingTimeStamp);
	CC_SYNTHESIZE(tm*, m_startDate, StartDate);
	CC_SYNTHESIZE(char*, m_sPath, csvPath);
	CC_SYNTHESIZE(int, m_currenttime, Currenttime);
	CC_SYNTHESIZE(int, m_lasttime, Lasttime);
private:
	static DataManager * m_dataManager;
	//const char* m_sPath;
};

class CsvData :public cocos2d::Ref
{
public:
	CREATE_FUNC(CsvData);
	virtual bool init();

	void addLineData(cocos2d::ValueVector lineData);//添加一行数据

	cocos2d::ValueVector getSingleLineData(int iLine);//获取某行数据

	cocos2d::Size getRowColNum();//获取行列大小
protected:
private:

	cocos2d::ValueVector m_allLineVec; //存放Csv文件所有行的数据，试试这样理解：ValueVector<Value<ValueVector>)
};
