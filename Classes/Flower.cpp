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
	if (!FilterSprite::init())
		return false;

	m_colorType = color;

	this->initWithFile(StringUtils::format("Res/flower_%d.png",color));

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


