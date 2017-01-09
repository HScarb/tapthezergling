#pragma once
#include "cocos2d.h"

class StringUtil :public cocos2d::Ref
{
public:
	static StringUtil * getInstance();
	virtual bool init();

	/* �÷ָ����ָ��ַ����������ŵ�һ���б��У��б��еĶ���ΪValue */
	cocos2d::ValueVector split(const char* srcStr, const char * sSep);
private:
	static StringUtil * m_stringUtil;
};