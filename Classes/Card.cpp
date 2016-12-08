//Card.cpp
#include "Card.h"
USING_NS_CC;

Card* Card::createByInfo(CardInfo info)
{
	auto card = new Card();
	if (card&&card->init(info))
	{
		card->autorelease();
		return card;
	}
	else
	{
		CC_SAFE_DELETE(card);
		return nullptr;
	}
}

bool Card::init(int info)
{
	if (!Sprite::init())
		return false;
	m_cardInfo = info;

	//根据卡片名称加载不同卡片
	this->initWithFile(StringUtils::format("Res/Cards/Card_%d.png", m_cardInfo));
	this->setAnchorPoint(Vec2(0, 0));
	return true;
	
}