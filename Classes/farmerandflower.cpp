#include "farmerandflower.h"
USING_NS_CC;

farmerandflower* farmerandflower::createByColor(int color)
{
	auto flower = new farmerandflower();

	if (flower && flower->init(color))
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

bool farmerandflower::init(int color)
{
	if (!Sprite::init())
		return false;

	m_colorType = color;

	//this->initWithFile(StringUtils::format("Res/flower_%d.png",color));

	switch (color)
	{
	case 1:
		this->initWithFile("res/Res/flower_1.png");
		break;
	case 2:
		this->initWithFile("res/Res/flower_2.png");
		break;
	case 3:
		this->initWithFile("res/Res/flower_3.png");
		break;
	case 4:
		this->initWithFile("res/Res/flower_4.png");
		break;
	case 5:
		this->initWithFile("Res/flower_5.png");
		break;
	case 6:
		this->initWithFile("Res/flower_6.png");
		break;
	default:
		break;
	}

	this->setAnchorPoint(Vec2(0, 0));		// 设置锚点为左下角

	return true;
}

void farmerandflower::eatAnimation()
{

}

void farmerandflower::tapped()
{
	this->removeFromParent();
}

