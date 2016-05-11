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