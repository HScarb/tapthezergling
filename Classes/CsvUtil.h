#pragma once
#include "cocos2d.h"
#include "DataManager.h"

using namespace cocos2d;

class CsvUtil : public Ref
{
public:
	static CsvUtil * getInstance();

	virtual bool init();

	void loadFile(const char * sPath);

	Value getValue(int iRow, int iCol, const char * csvFilePath);

	const std::string get(int iRow, int iCol, const char * csvFilePath);

	const int getInt(int iRow, int iCol, const char * csvFilePath);

	const float getFloat(int iRow, int iCol, const char * csvFilePath);

	const bool getBool(int iRow, int iCol, const char * csvFilePath);

	const Size getFileRowColNum(const char * csvFilePath);

	const int findValueInWithLine(const char * chValue, int iValueCol, const char* csvFilePath);

	void flashCsv(const char* csvFilePath);
private:
	static CsvUtil* m_csvUtil;
	std::string m_sPath;
	Map<std::string, CsvData*> m_csvMap;
};