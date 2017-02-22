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

struct CardData
{
public:
	int info;		// ��Ƭ����
	int level;		// ��Ƭ�ȼ�
	int num;		// �����͵ȼ���Ƭ������
	CardData()
	{
		this->info = 0;
		this->level = 0;
		this->num = 0;
	}
	CardData(int info, int level, int num)
	{
		this->info = info;
		this->level = level;
		this->num = num;
	}
};

class DataManager : public cocos2d::Node
{
public:
	static DataManager * getInstance();
	virtual bool init() override;

	void saveData();
	void loadData();
	void saveCardData();
	void loadCardData();

	void initCardData();								// ��ʼ����Ƭ�����ļ�
	void pushBackACard(int type, int level);			// ��m_cardData�м�һ�ſ�Ƭ

	CC_SYNTHESIZE(int, m_bestScore, BestScore);
	CC_SYNTHESIZE(int, m_jewel, Jewel);
	CC_SYNTHESIZE(int, m_energy, Energy);
	CC_SYNTHESIZE(int, m_lastLoginDate, LastLoginDate);
	CC_SYNTHESIZE(int, m_startCollectionTime, StartTimeStamp);
	CC_SYNTHESIZE(int, m_endCollectionTime, EndingTimeStamp);
	CC_SYNTHESIZE(tm*, m_startDate, StartDate);

	CC_SYNTHESIZE(std::string, _cardDataPath, CardDataPath);				// ��Ƭ���ݴ��·��
	CC_SYNTHESIZE(std::vector<CardData*>, m_cardData, CardData);			// ��vector�洢��Ƭ����
private:
	static DataManager * m_dataManager;

};
