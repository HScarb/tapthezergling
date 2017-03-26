//Card.cpp
#include "Card.h"
USING_NS_CC;

Card* Card::createByLevelAndInfo(int level, int info)
{
	auto card = new Card();
	if (card&&card->init(info,level))
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

bool Card::init(int info,int level)
{
	if (!Sprite::init())
		return false;
	m_cardInfo = info;
	m_cardLevel = level;
	//根据卡片名称加载不同卡片

	switch (m_cardInfo)
	{
	case 1:
		this->initWithFile(StringUtils::format("Res/Cards/Card_DoubleTap_%d.jpg", m_cardLevel));
		break;
	case 2:
		this->initWithFile(StringUtils::format("Res/Cards/Card_SlideCut_%d.jpg", m_cardLevel));
		break;
	case 3:
		this->initWithFile(StringUtils::format("Res/Cards/Card_EatFlowers_%d.jpg", m_cardLevel));
		break;
	case 4:
		this->initWithFile(StringUtils::format("Res/Cards/Card_BurrowAndAttack_%d.jpg", m_cardLevel));
		break;
	case 5:
		this->initWithFile(StringUtils::format("Res/Cards/Card_JumpingOnPool_%d.jpg", m_cardLevel));
		break;
	case 6:
		this->initWithFile(StringUtils::format("Res/Cards/Card_ClassifyUnits_%d.jpg", m_cardLevel));
		break;
	case 7:
		this->initWithFile(StringUtils::format("Res/Cards/Card_BOSS1_%d.jpg", m_cardLevel));
		break;
	case 8:
		this->initWithFile(StringUtils::format("Res/Cards/Card_BOSS2_%d.jpg", m_cardLevel));
		break;
	case 9:
		this->initWithFile(StringUtils::format("Res/Cards/Card_CheckTheThing_%d.jpg", m_cardLevel));
		break;
	case 10:
		this->initWithFile(StringUtils::format("Res/Cards/Card_FeadSnacks_%d.jpg", m_cardLevel));
		break;
	}
	//this->initWithFile(StringUtils::format("Res/Cards/Card_%d.png", m_cardInfo));
	this->setAnchorPoint(Vec2(0, 0));
	return true;
	
}