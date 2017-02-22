// DataManager.cpp
#include "DataManager.h"
#include "CsvUtil.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "TimeManager.h"
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
	m_lastLoginDate = 0;
	_cardDataPath = FileUtils::getInstance()->getWritablePath() + "cardData.json";
	return true;
}

void DataManager::saveData()
{
	UserDefault::getInstance()->setIntegerForKey("bestScore", m_bestScore);
	UserDefault::getInstance()->setIntegerForKey("jewel", m_jewel);
	UserDefault::getInstance()->setIntegerForKey("energy", m_energy);
	UserDefault::getInstance()->setIntegerForKey("lastLoginDate", m_lastLoginDate);
	UserDefault::getInstance()->flush();

	saveCardData();

	CCLOG("Data saved");
}

void DataManager::loadData()
{
	TimeManager::getInstance()->getCurrentDateTime();
	int loaded_bestScore = UserDefault::getInstance()->getIntegerForKey("bestScore", 0);
	if (loaded_bestScore > m_bestScore)
		m_bestScore = loaded_bestScore;
	m_jewel = UserDefault::getInstance()->getIntegerForKey("jewel", 0);
	m_energy = UserDefault::getInstance()->getIntegerForKey("energy", 0);
	m_lastLoginDate = UserDefault::getInstance()->getIntegerForKey("lastLoginDate", 0);
	CCLOG("Data loaded.\n");
	CCLOG("bestScore = %d\n", m_bestScore);
	CCLOG("jewel = %d\n", m_jewel);
	CCLOG("energy = %d\n", m_energy);
	CCLOG("lastLoginDate = %d\n", m_lastLoginDate);
	CCLOG("XML path: %s", UserDefault::getInstance()->getXMLFilePath());

	loadCardData();
}

void DataManager::saveCardData()
{
	// ----- �洢card data -----
	Document document;
	document.SetObject();
	Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value info_array(rapidjson::kArrayType);
	// ��m_cardData�����е����ݼ����д���array
	for (auto item : m_cardData)
	{
		rapidjson::Value object(rapidjson::kObjectType);
		object.SetObject();
		object.AddMember("info", item->info, allocator);
		object.AddMember("level", item->level, allocator);
		object.AddMember("num", item->num, allocator);
		info_array.PushBack(object, allocator);
	}
	document.AddMember("cardData", info_array, allocator);
	// ����json��ʽ��д���ļ�
	StringBuffer buffer;
	PrettyWriter<StringBuffer> writer(buffer);
	document.Accept(writer);
	FILE * file = fopen(FileUtils::getInstance()->getSuitableFOpen(_cardDataPath).c_str(), "w");
	fprintf(file, buffer.GetString());
	fclose(file);
}

void DataManager::loadCardData()
{
	// ----- ����json�����ļ� -----
	string cardDataJson = FileUtils::getInstance()->getStringFromFile(_cardDataPath);
	const int strlen = cardDataJson.length();
	char * buffer = new char[strlen];
	memcpy(buffer, cardDataJson.c_str(), strlen);
	CCLOG("Card Data Path: %s", _cardDataPath);
	Document document;
	if (document.Parse(cardDataJson.c_str()).HasParseError())				// ����json�ļ���������������򴴽�һ���µ�cardData�ļ�
	{
		CCLOG("Parse In-situ error, create a new card data file.");
		initCardData();												// ����һ���µĿյ�cardData.json�ļ�
		return;
	}
	else
	{
		CCLOG("Parse In-situ test passed.");
		const rapidjson::Value& dataArray = document["cardData"];

		if (dataArray.IsArray())
		{
			for (int i = 0; i < dataArray.Size(); i++)
			{
				const rapidjson::Value& object = dataArray[i];

				auto card = new CardData();
				card->info = object["info"].GetInt();
				card->level = object["level"].GetInt();
				card->num = object["num"].GetInt();

				m_cardData.push_back(card);
			}
		}
		else
		{
			CCLOG("Parse json data error.");
		}
	}
}

// ����һ���µĿյ�cardData�ļ�
void DataManager::initCardData()
{
	auto fileutils = FileUtils::getInstance();
	CCLOG("SuitableFOpen: %s", fileutils->getSuitableFOpen(_cardDataPath));
	FILE * file = fopen(fileutils->getSuitableFOpen(_cardDataPath).c_str(), "w");
	fprintf(file, "");
	fclose(file);
	CCLOG("Finish initing card data.");
}

void DataManager::pushBackACard(int type, int level)
{
	bool hasType = false;									// �������Ƿ��Ѿ�����ͬ�Ŀ�Ƭ
	for(auto item : m_cardData)
	{
		if (item->info == type && item->level == level)		// ����Ѿ�����ͬ�Ŀ�Ƭ����������1
		{
			item->num++;
			hasType = true;
		}
	}
	// ���û����ͬ�Ŀ�Ƭ�����½�һ��CardData�ṹ�壬ѹ������
	if(!hasType)
	{
		auto cd = new CardData(type, level, 1);
		m_cardData.push_back(cd);
	}
	// ��������
//	saveCardData();
}