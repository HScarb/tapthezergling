// ClassifyUnits.h
#pragma once
#include "cocos2d.h"
#include "TollgateControlLayer.h"

class Unit : public cocos2d::Sprite
{
public:
	typedef enum
	{
		NONE = 0,
		SCV,
		Drone,
		Probe,
		Zergling
	} UnitType;
	static Unit * create(UnitType type);
	bool initWithType(UnitType type);

	cocos2d::Vec2 getPosByRow();

	CC_SYNTHESIZE(int, m_row, Row);
	CC_SYNTHESIZE(UnitType, m_type, Type);
};

class ClassifyUnits : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	bool init(int diff, int loop);
	static cocos2d::Layer * create(int diff, int loop);

	void initUnits();
	void addAGroupOfUnits();
	void moveUnits();

	virtual bool onTouchBegan(cocos2d::Touch * pTouch, cocos2d::Event * pEvent);

private:
	int m_diff, m_loop;
	bool m_isRunning, m_isMoving;
	TollgateControlLayer * m_controlLayer;

	cocos2d::Vector<Unit*> m_unitVector;
	cocos2d::Vector<Unit*> m_unitShowVector;
	
	// buildings
	cocos2d::Sprite * m_terranBase;
	cocos2d::Sprite * m_zergBase;
	cocos2d::Sprite * m_protossBase;
	cocos2d::Sprite * m_spawningPool;
};