#pragma once
#include "cocos2d.h"

class StringUtil :public cocos2d::Ref
{
public:
	static StringUtil * getInstance();
	virtual bool init();

	/* 用分隔符分割字符串，结果存放到一个列表中，列表中的对象为Value */
	cocos2d::ValueVector split(const char* srcStr, const char * sSep);
private:
	static StringUtil * m_stringUtil;
};