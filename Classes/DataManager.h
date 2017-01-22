// DataManager
/*
	��������ʹ洢�û�����Ϸ��Ϣ
	- ʱ��
	- ����
	- ��ʯ
	- ����
	- ��Ƭ
	- �ȵ�
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

	void addLineData(cocos2d::ValueVector lineData);//���һ������

	cocos2d::ValueVector getSingleLineData(int iLine);//��ȡĳ������

	cocos2d::Size getRowColNum();//��ȡ���д�С
protected:
private:

	cocos2d::ValueVector m_allLineVec; //���Csv�ļ������е����ݣ�����������⣺ValueVector<Value<ValueVector>)
};
