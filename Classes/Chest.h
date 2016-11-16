//Chest.h
#pragma once
#include "cocos2d.h"
#include "FilterSprite.h"

class Chest : public FilterSprite
{
public:
	enum ChestColor
	{
		NONE = 0,
		BLUE,
		YELLOW
	};

	static Chest * createByColor(ChestColor color = NONE);
	bool init(int color);

	//void tapped();			// ������Ժ���ʧ�����ֱ�ʯ���߿�Ƭ������
	CC_SYNTHESIZE(int, m_colorType, ColorType);
};