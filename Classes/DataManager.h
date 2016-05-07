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

private:
	static DataManager * m_dataManager;

};