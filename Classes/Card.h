//Card.h
#pragma once
#include "cocos2d.h"

class Card : public cocos2d::Sprite
{
public:
	enum CardInfo
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
		Zergling_King_Card,
		Zergling_Ninja_Card
	};//¿¨Æ¬Ãû³Æ
	static Card * createByInfo(CardInfo info = NONE);
	bool init(int info);

	void tapped();//¿¨Æ¬µã»÷²Ù×÷
	CC_SYNTHESIZE(int, m_cardInfo, Cardinfo);
	CC_SYNTHESIZE(int, m_cardLevel, CardLevel);
};
