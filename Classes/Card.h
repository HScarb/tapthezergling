//Card.h
#pragma once
#include "cocos2d.h"

class Card : public cocos2d::Sprite
{
public:
	typedef enum
	{
		NONE = 0,
		Double_Tap_Zergling_Card = 1,
		Slide_Cut_Card,
		Eat_Flowers_Card,
		Burrow_And_Attack_Card,
		Jumping_On_Pools_Card,
		Classify_Units_Card,
		Check_The_Units_Card,
		Feed_Snakes_Card,
		//Fit_The_Circle_Card,
		Zergling_King_Card,
		Zergling_Ninja_Card
	} CardInfo;//¿¨Æ¬Ãû³Æ
	static Card * createByLevelAndInfo(int level,int info = 0);
	bool init(int info,int level);

	void tapped();//¿¨Æ¬µã»÷²Ù×÷

	CC_SYNTHESIZE(int, m_cardInfo, Cardinfo);
	CC_SYNTHESIZE(int, m_cardLevel, CardLevel);
};
