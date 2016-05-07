#include "Food.h"
USING_NS_CC;

Food* Food::createByType(Foodtype type)
{
	auto flower = new Food();

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

bool Food::init(int type)
{
	if (!FilterSprite::init())
		return false;

	m_colorType = type;

	// 根据资源名加载不同颜色的花
	// this->initWithTexture(Texture2D::, Rect::ZERO);
	this->initWithFile(StringUtils::format("Res/flower_%d.png", m_colorType));//暂时只有三种

	this->setAnchorPoint(Vec2(0, 0));		// 设置锚点为左下角

	return true;
}

void Food::eatAnimation()
{

}

void Food::tapped()
{
	this->removeFromParent();
}
