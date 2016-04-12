//EatCandiesScene.h
#ifndef EATCANDIESSCENE_H
#define EATCANDIESSCENE_H

#pragma once
#include "cocos2d.h"

USING_NS_CC;

class EatCandiesScene : public Sprite
{
public:
	int newLevel(int diff, int loop);
	static EatCandiesScene* createByType(int type);//根据糖果类型,假设糖果种类有三种？
	bool init(int type);
	int getType(){ return m_type; }								//取决于糖果有几张不同的图片
	int getX(){ return m_x; }
	int getY(){ return m_y; }
	bool isCrushing(){ return m_isCrushing; }
	void crush();//消除，点击时消除这个糖果

private:
	int m_type;//种类
	int m_x;//X坐标
	int m_y;//Y坐标
	bool m_isCrushing;//是否正在消除
};

#endif