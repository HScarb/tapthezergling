#include "StringUtil.h"

using namespace cocos2d;

StringUtil * StringUtil::m_stringUtil;

StringUtil* StringUtil::getInstance()
{
	if (m_stringUtil == NULL)
	{
		m_stringUtil = new StringUtil();
		if (m_stringUtil&&m_stringUtil->init())
		{
			m_stringUtil->autorelease();
			m_stringUtil->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_stringUtil);
			m_stringUtil = NULL;
		}
	}
	return m_stringUtil;
}

bool StringUtil::init()
{
	return true;
}

cocos2d::ValueVector StringUtil::split(const char* srcStr, const char* sSep)
{
	cocos2d::ValueVector stringList;
	int size = strlen(srcStr);
	
	cocos2d::Value str = cocos2d::Value(srcStr);//数据转换为字符串

	int startIndex = 0;
	int endIndex = 0;
	endIndex = str.asString().find(sSep);

	std::string lineStr;

	while (endIndex > 0)//根据换行符拆分字符串，并添加到列表
	{
		lineStr = str.asString().substr(startIndex, endIndex);//截取一行字符

		stringList.push_back(cocos2d::Value(lineStr));//添加到列表

		str = Value(str.asString().substr(endIndex + 1, size));//截取剩下的字符串

		endIndex = str.asString().find(sSep);
	}
	if (str.asString().compare("") != 0)//剩下的字符串也添加进列表
	{
		stringList.push_back(Value(str.asString()));
	}
	return stringList;
}