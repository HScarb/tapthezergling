// GlobalDefine.h
#pragma once

// 1 - convenience measurements
#define SCREEN Director::getInstance()->getWinSize()
#define CENTER Vec2(SCREEN.width / 2, SCREEN.height / 2)
#define CURTIME do {                                                        \
    timeval time;                                                           \
    gettimeofday(&time, NULL);                                              \
    unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000); \
    return (float)millisecs;                                                \
} while (0)

// 2 - file path
	// units
#define PATH_SCV "Workers/SCs_SCV_C_01.png"
#define PATH_DRONE "Workers/SCs_Drone_C_01.png"
#define PATH_PROBE "Workers/SCs_Probe_C_01.png"
#define PATH_SMALLZERGLING "zergling/SCs_Zergling_C3_04.png"
	// buildings
#define PATH_ZERG_BASE "star crafts/SCs_Hatchery_C.png"
#define PATH_TERRAN_BASE "star crafts/SCs_CommandCenter_C.png"
#define PATH_PROTOSS_BASE "star crafts/SCs_Nexus_C.png"
#define PATH_SPAWNINGPOOL "star crafts/SCs_SpawningPool_C.png"
	// pics
#define PATH_BUTTON_ACCEPT_1 "RESOURCE/button_accept_1.png"
#define PATH_BUTTON_ACCEPT_2 "RESOURCE/button_accept_2.png"
#define PATH_ADD_TWO "RESOURCE/add_two.png"
