#include "Flower.h"
USING_NS_CC;

Flower* Flower::createByColor(int color)
{
	auto flower = new Flower();

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

bool Flower::init(int color)
{
	if (!Sprite::init())
		return false;

	m_colorType = color;

	//this->initWithFile(StringUtils::format("Res/flower_%d.png",color));

	switch (color)
	{
	case 1:
		this->initWithFile("res/Res/flower/flower_1.png");
		break;
	case 2:
		this->initWithFile("res/Res/flower/flower_2.png");
		break;
	case 3:
		this->initWithFile("res/Res/flower/flower_3.png");
		break;
	case 4:
		this->initWithFile("res/Res/flower/flower_4.png");
		break;
	default:
		break;
	}

	this->setAnchorPoint(Vec2(0, 0));		// 设置锚点为左下角

	return true;
}

void Flower::eatAnimation()
{

}

void Flower::tapped()
{
	this->removeFromParent();
}


