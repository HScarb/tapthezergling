// GlobalConst.h
/*
	存储全局常数
*/
#pragma once
#include <string>

const float INITIAL_TIME = 5.0f;
const int TOTAL_TOLLGATE_TYPE = 10;
const int TOTAL_BOSS_TYPE = 2;
const int CHEST_TOLLGATE = 1;			// 每几关出现关卡
const std::string TOLLGATE_NAME[11] = 
{
	"0: None",
	"1: Double Tap Zergling",
	"2: Slide Cut",
	"3: Eat Flowers",
	"4: Burrow And Attack",
	"5: Jumping On Pools",
	"6: Classify Units",
	"7: Check The Units",
	"8: Feed Snakes",
	"9: Fit The Circle",
	"10: Run Run Run"
};
const std::string BOSS_TOLLGATE_NAME[3] =
{
	"0: None",
	"Boss1: Zergling King",
	"Boss2: Zergling Ninja"
};

const int ZORDER_TOLLGATECONTROLLAYER = 100;

const std::string TOLL_NAME[] =
{
	"None",
	"DoubleTap",
	"SlideCut",
	"EatFlowers",
	"BurrowAndAttack",
	"JumpingOnPools",
	"ClassifyUnits",
	"ZerglingKing",
	"ZerglingNinja",
	"CheckTheUnits",
	"FeedSnakes",
	"RunRunRun"
};
const std::string CARD_NAME[] =
{
	"None",
	"ZerglingCouple",
	"Zealot Cutter",
	"Reaver",
	"Infestor",
	"PiKaLing",
	"Queen",
	"Ultralisk",
	"Thor",
	"Overseer",
	"ZerglingBrothers"
};