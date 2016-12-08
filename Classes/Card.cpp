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

	switch (m_cardInfo)
	{
	case 1:
		this->initWithFile(StringUtils::format("Res/Cards/Card_DoubleTap.jpg"));
		break;
	case 2:
		this->initWithFile(StringUtils::format("Res/Cards/Card_SlideCut.jpg"));
		break;
	case 3:
		this->initWithFile(StringUtils::format("Res/Cards/Card_EatFlowers.jpg"));
		break;
	case 4:
		this->initWithFile(StringUtils::format("Res/Cards/Card_BurrowAndAttack.jpg"));
		break;
	case 5:
		this->initWithFile(StringUtils::format("Res/Cards/Card_JumpingOnPool.jpg"));
		break;
	case 6:
		this->initWithFile(StringUtils::format("Res/Cards/Card_ClassifyUnits.jpg"));
		break;
	case 7:
		this->initWithFile(StringUtils::format("Res/Cards/Card_BOSS1.jpg"));
		break;
	case 8:
		this->initWithFile(StringUtils::format("Res/Cards/Card_BOSS2.jpg"));
		break;
	case 9:
		this->initWithFile(StringUtils::format("Res/Cards/Card_CheckTheThing.jpg"));
		break;
	case 10:
		this->initWithFile(StringUtils::format("Res/Cards/Card_FeadSnacks.jpg"));
		break;
	}
	//this->initWithFile(StringUtils::format("Res/Cards/Card_%d.png", m_cardInfo));
	this->setAnchorPoint(Vec2(0, 0));
	return true;
	
}