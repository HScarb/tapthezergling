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
	int info;		// ��Ƭ����
	int level;		// ��Ƭ�ȼ�
	int num;		// �����͵ȼ���Ƭ������
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

	CC_SYNTHESIZE(std::string, _cardDataPath, CardDataPath);				// ��Ƭ���ݴ��·��
	CC_SYNTHESIZE(std::vector<CardData*>, m_cardData, CardData);			// ��vector�洢��Ƭ����
private:
	static DataManager * m_dataManager;

};
