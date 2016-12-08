// GlobalConst.h
/*
	存储全局常数
*/
#pragma once
#include <string>

const float INITIAL_TIME = 5.0f;
const int TOTAL_TOLLGATE_TYPE = 8;
const int CHEST_TOLLGATE = 5;			// 每几关出现关卡
const std::string TOLLGATE_NAME[9] = 
{
	"0: None",
	"1: Double Tap Zergling",
	"2: Slide Cut",
	"3: Eat Flowers",
	"4: Burrow And Attack",
	"5: Jumping On Pools",
	"6: Classify Units",
	"7: Check The Units",
	"8: Feed Snakes"
};
const std::string BOSS_TOLLGATE_NAME[3] =
{
	"0: None",
	"Boss1: Zergling King",
	"Boss2: Zergling Ninja"
};

const int ZORDER_TOLLGATECONTROLLAYER = 100;

const std::string CARD_NAME[] =
{
	"None",
	"Double Tap Zergling Card",
	"Slide Cut Card",
	"Eat Flowers Card",
	"Burrow And Attack Card",
	"Jumping On Pools Card",
	"Classify Units Card",
	"Check The Units Card",
	"Feed Snakes Card"
	"Zergling King Card",
	"Zergling Ninja Card"
};
