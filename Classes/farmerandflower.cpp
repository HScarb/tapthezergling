#include "farmerandflower.h"
USING_NS_CC;


Farmerandflower* Farmerandflower::farmerandflowerAppear(int type)
{
	auto flower = new Farmerandflower();

	if (flower && flower->init(type))
	{
		flower->autorelease();
		return flower;
	}
	else
	{
		CC_SAFE_DELETE(flower);
		return nullptr;
	}
}

bool Farmerandflower::init(int color)
{
	if (!FilterSprite::init())
		return false;

	m_colorType = color;

	switch (color)
	{
	case 1:
		this->initWithFile("Res/Workers/SCs_SCV_C_01.PNG");
		break;
	case 2:
		this->initWithFile("Res/Workers/SCs_Drone_C_01.PNG");
		break;
	case 3:
		this->initWithFile("Res/Workers/SCs_Probe_C_01.PNG");
		break;
	case 4:
		this->initWithFile("Res/flower_1.png");
		break;
	case 5:
		this->initWithFile("Res/flower_2.png");
		break;
	case 6:
		this->initWithFile("Res/flower_3.png");
		break;
	default:
		break;
	}

	this->setAnchorPoint(Vec2(0, 0));		// ����ê��Ϊ���½�

	return true;
}

void Farmerandflower::tapped()
{
	this->removeFromParent();
}