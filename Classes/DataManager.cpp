// DataManager.cpp
#include "DataManager.h"
USING_NS_CC;

DataManager * DataManager::m_dataManager = nullptr;

DataManager* DataManager::getInstance()
{
	if (m_dataManager == nullptr)
	{
		m_dataManager = new DataManager();
		if (m_dataManager && m_dataManager->init())
		{
			m_dataManager->autorelease();
			m_dataManager->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_dataManager);
			m_dataManager = nullptr;
		}
	}
	return m_dataManager;
}

bool DataManager::init()
{
	if (!Node::init())
		return false;

	m_bestScore = 0;
	m_jewel = 0;
	m_energy = 0;

	return true;
}

void DataManager::saveData()
{
	UserDefault::getInstance()->setIntegerForKey("bestScore", m_bestScore);
	UserDefault::getInstance()->setIntegerForKey("jewel", m_jewel);
	UserDefault::getInstance()->setIntegerForKey("energy", m_energy);
	UserDefault::getInstance()->flush();
	CCLOG("Data saved");
}

void DataManager::loadData()
{
	int loaded_bestScore = UserDefault::getInstance()->getIntegerForKey("bestScore", 0);
	if (loaded_bestScore > m_bestScore)
		m_bestScore = loaded_bestScore;
	m_jewel = UserDefault::getInstance()->getIntegerForKey("jewel", 0);
	m_energy = UserDefault::getInstance()->getIntegerForKey("energy", 0);
	CCLOG("Data loaded.\n");
	CCLOG("bestScore = %d\n", m_bestScore);
	CCLOG("jewel = %d\n", m_jewel);
	CCLOG("energy = %d\n", m_energy);
	CCLOG("XML path: %s", UserDefault::getInstance()->getXMLFilePath());
}