// AnimationUtil.h
#pragma once
#include "cocos2d.h"

class AnimationUtil
{
public:
	/*
	
	*/
	static cocos2d::Animation * createWithSingleFrameName(const char * name, float delay, int iLoops, bool restoreOriginalFrame = true);

	/*
	
	*/
	static cocos2d::Animation * createWithFrameNameAndNum(const char * name, int iNum, float delay, int iLoops, bool restoreOriginalFrame = true);

	static cocos2d::Animation * createWithFrameNameAndNumRange(const char* iName, int startNum, int endNum, float delay, int iLoops, bool restoreOriginalFrame = true);
};