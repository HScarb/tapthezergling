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
	
	cocos2d::Value str = cocos2d::Value(srcStr);//����ת��Ϊ�ַ���

	int startIndex = 0;
	int endIndex = 0;
	endIndex = str.asString().find(sSep);

	std::string lineStr;

	while (endIndex > 0)//���ݻ��з�����ַ���������ӵ��б�
	{
		lineStr = str.asString().substr(startIndex, endIndex);//��ȡһ���ַ�

		stringList.push_back(cocos2d::Value(lineStr));//��ӵ��б�

		str = Value(str.asString().substr(endIndex + 1, size));//��ȡʣ�µ��ַ���

		endIndex = str.asString().find(sSep);
	}
	if (str.asString().compare("") != 0)//ʣ�µ��ַ���Ҳ��ӽ��б�
	{
		stringList.push_back(Value(str.asString()));
	}
	return stringList;
}