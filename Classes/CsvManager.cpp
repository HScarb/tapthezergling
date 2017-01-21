#include "CsvManager.h"

bool CsvManager::init()
{
	return true;
}

void CsvManager::addLineData(ValueVector lineData)
{
	m_allLineVec.push_back(Value(lineData));
}

cocos2d::ValueVector CsvManager::getSingleLineData(int iLine)
{
	return m_allLineVec.at(iLine).asValueVector();
}

Size CsvManager::getRowColNum()
{
	Size size = Size();

	size.width = m_allLineVec.size();

	if (size.width > 0) {
		size.height = m_allLineVec.at(0).asValueVector().size();
	}

	return size;
}