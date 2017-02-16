// DataManager.cpp
#include "DataManager.h"
#include "CsvUtil.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
using namespace rapidjson;
USING_NS_CC;
using namespace std;

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
	_cardDataPath = FileUtils::getInstance()->getWritablePath() + "cardData.json";
	return true;
}

void DataManager::saveData()
{
	UserDefault::getInstance()->setIntegerForKey("bestScore", m_bestScore);
	UserDefault::getInstance()->setIntegerForKey("jewel", m_jewel);
	UserDefault::getInstance()->setIntegerForKey("energy", m_energy);
	UserDefault::getInstance()->flush();

	// 存储card data
	/*for(auto item : m_cardData)
	{
		
	}*/
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
/*
	//CsvUtil::getInstance()->flashCsv(m_sPath);
	CsvUtil::getInstance()->loadFile(m_sPath);
	Value fcn=CsvUtil::getInstance()->getValue(0,2,m_sPath);
	log("firstMonsterName = %s", fcn.asString().c_str());
*/
	// 加载json数据文件
	string cardData = FileUtils::getInstance()->getStringFromFile(_cardDataPath);
	const int strlen = cardData.length();
	char * buffer = new char[strlen];
	memcpy(buffer, cardData.c_str(), strlen);
	CCLOG("Card Data Path: %s", _cardDataPath);
	Document document;
	if (document.ParseInsitu(buffer).HasParseError())				// 解析json文件，如果解析出错，则创建一个新的cardData文件
	{
		CCLOG("Parse In-situ error, create a new card data file.");
		initCardData();												// 创建一个新的空的cardData.json文件
		return;
	}
	else
	{
		CCLOG("Parse In-situ test passed.");
		const rapidjson::Value& a = document["cardData"];

		static const char* kTypeNames[] =
			{ "Null", "False", "True", "Object", "Array", "String", "Number" };
		for (rapidjson::Value::ConstMemberIterator itr = document["cardData"].MemberBegin(); itr != document["cardData"].MemberEnd(); ++itr)
		{
			CCLOG("Type of member %s is %s\n", itr->name.GetString(), kTypeNames[itr->value.GetType()]);
		}
	}

}

// 创建一个新的空的cardData文件
void DataManager::initCardData()
{
	auto fileutils = FileUtils::getInstance();
	CCLOG("SuitableFOpen: %s", fileutils->getSuitableFOpen(_cardDataPath));
	FILE * file = fopen(fileutils->getSuitableFOpen(_cardDataPath).c_str(), "w");
	fprintf(file, "");
	fclose(file);
	CCLOG("Finish initing card data.");
}
