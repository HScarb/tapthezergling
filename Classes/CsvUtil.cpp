#include "CsvUtil.h"
#include "StringUtil.h"
#include<iostream>
#include<fstream>
#include "Card.h"
#include "CardManager.h"

CsvUtil* CsvUtil::m_csvUtil = NULL;

CsvUtil* CsvUtil::getInstance()
{
	if (m_csvUtil == NULL)
	{
		m_csvUtil = new CsvUtil();
		if (m_csvUtil&&m_csvUtil->init())
		{
			m_csvUtil->autorelease();
			m_csvUtil->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_csvUtil);
			m_csvUtil = NULL;
		}
	}
	return m_csvUtil;

}

bool CsvUtil::init()
{
	//m_sPath = "Cards.csv";
	m_sPath = StringUtils::format("Resources/res/Cards.csv");
	return true;
}

void CsvUtil::loadFile(const char* sPath)
{
	CsvData * csvData = CsvData::create();

	std::string str = FileUtils::getInstance()->getStringFromFile(sPath);
	ValueVector lineList = StringUtil::getInstance()->split(str.c_str(), "\n");

	for (auto value : lineList)
	{
		ValueVector tArr = StringUtil::getInstance()->split(value.asString().c_str(), ",");
		csvData->addLineData(tArr);
	}
	m_csvMap.insert(sPath, csvData);
}

Value CsvUtil::getValue(int iRow, int iCol, const char* csvFilePath)
{
	auto csvData = m_csvMap.at(csvFilePath);

	if (csvData == nullptr)
	{
		loadFile(csvFilePath);
		csvData = m_csvMap.at(csvFilePath);
	}
	Size size = csvData->getRowColNum();

	int iRowNum = size.width;
	int iColNum = size.height;

	if (iRow >= iRowNum || iCol >= iColNum)
		return Value("");

	ValueVector rowVector = csvData->getSingleLineData(iRow);

	Value colValue = rowVector.at(iCol);

	return colValue;
}

const std::string CsvUtil::get(int iRow, int iCol, const char* csvFilePath)
{
	Value colValue = getValue(iRow, iCol, csvFilePath);
	return colValue.asString();
}

const int CsvUtil::getInt(int iRow, int iCol, const char* csvFilePath)
{
	Value colValue = getValue(iRow, iCol, csvFilePath);
	return colValue.asInt();
}

const float CsvUtil::getFloat(int iRow, int iCol, const char* csvFilePath)
{
	Value colValue = getValue(iRow, iCol, csvFilePath);
	return colValue.asFloat();
}

const bool CsvUtil::getBool(int iRow, int iCol, const char* csvFilePath)
{
	Value colValue = getValue(iRow, iCol, csvFilePath);
	return colValue.asBool();
}

const Size CsvUtil::getFileRowColNum(const char* csvFilePath)
{
	/* 取出配置文件的二维表格 */
	auto csvData = m_csvMap.at(csvFilePath);

	/* 如果配置文件的数据不存在，则加载配置文件 */
	if (csvData == nullptr) {
		loadFile(csvFilePath);
		csvData = m_csvMap.at(csvFilePath);
	}
	Size size = csvData->getRowColNum();
	return size;
}

const int CsvUtil::findValueInWithLine(const char* chValue, int iValueCol, const char* csvFilePath)
{
	Size csvSize = getFileRowColNum(csvFilePath);
	int iLine = -1;
	for (int i = 2; i < csvSize.width; i++) {
		int ID = getInt(i, iValueCol, csvFilePath);
		if (Value(ID).asString().compare(chValue) == 0) {
			iLine = i;
			break;
		}
	}
	return iLine;
}

void CsvUtil::flashCsv(const char* csvFilePath)
{
	if (CardManager::getInstance()->getAllCards().size() == 0)
	{
		//创建卡片
		for (int i = 25; i >= 1; i--)
		{
			/*if (i > 10)
			{
			auto card = CardManager::getInstance()->CreateACardByTypeAndLevel((Card::CardInfo)(random(1,10)), 1, i - 1);
			this->addChild(card);
			}
			else
			{
			auto card = CardManager::getInstance()->CreateACardByTypeAndLevel((Card::CardInfo)1, 1, i - 1);
			this->addChild(card);
			}*/
			auto card = CardManager::getInstance()->CreateACardByTypeAndLevel((Card::CardInfo)(random(1, 10)), 1, 0);
		}
	}
	CardManager::getInstance()->SortCardMsg();
	/*char filename[] = "Cards.csv";
	std::ofstream fout(filename);
	fout << "Name,Level,Position" << std::endl;
	
	for (auto card : CardManager::getInstance()->getAllCards())
	{
		fout << StringUtils::format("%d", card->getCardinfo()) << "," << StringUtils::format("%d", card->getCardLevel()) << "," << StringUtils::format("%d", card->getPosition().y) << std::endl;
	}*/
	FileUtils::getInstance()->writeStringToFile("Name,Level,Position", m_sPath);
}