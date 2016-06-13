#include "farmerandflower.h"
USING_NS_CC;


Farmerandflower* Farmerandflower::farmerandflowerAppear(int color)
{
	auto flowerandflower = new Farmerandflower();

	if (flowerandflower && flowerandflower->init(color))
	{
		flowerandflower->autorelease();
		return flowerandflower;
	}
	else
	{
		CC_SAFE_DELETE(flowerandflower);
		return nullptr;
	}
}

bool Farmerandflower::init(int color)
{
	if (!Sprite::init())
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

	this->setAnchorPoint(Vec2(0, 0));		// 设置锚点为左下角

	return true;
}

void Farmerandflower::tapped()
{
	this->removeFromParent();
}

