// BOSS1ZerglingKing.h
#pragma once
#include "cocos2d.h"

class BOSS1ZerglingKing : cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	CREATE_FUNC(BOSS1ZerglingKing);
	virtual bool init() override;

private:
	bool m_isRunning;
};
