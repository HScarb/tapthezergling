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
	static EatCandiesScene* createByType(int type);//�����ǹ�����,�����ǹ����������֣�
	bool init(int type);
	int getType(){ return m_type; }								//ȡ�����ǹ��м��Ų�ͬ��ͼƬ
	int getX(){ return m_x; }
	int getY(){ return m_y; }
	bool isCrushing(){ return m_isCrushing; }
	void crush();//���������ʱ��������ǹ�

private:
	int m_type;//����
	int m_x;//X����
	int m_y;//Y����
	bool m_isCrushing;//�Ƿ���������
};

#endif