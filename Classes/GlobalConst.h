// GlobalConst.h
/*
	存储全局常数
*/
#pragma once
#include <string>

const float INITIAL_TIME = 5.0f;
const int TOTAL_TOLLGATE_TYPE = 6;
const std::string TOLLGATE_NAME[TOTAL_TOLLGATE_TYPE + 1] = 
{
	"None",
	"Double Tap Zergling",
	"Slide Cut",
	"Eat Flowers",
	"Burrow And Attack",
	"Jumping On Pools",
	"Classify Units"
};