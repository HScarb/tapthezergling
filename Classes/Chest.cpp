#include "Chest.h"

USING_NS_CC;

Chest* Chest::createByColor(ChestColor color)
{
	auto chest = new Chest();

	if (chest && chest->init(color))
	{
		chest->autorelease();
		return chest;
	}
	else
	{
		CC_SAFE_DELETE(chest);
		return nullptr;
	}
}

bool Chest::init(int color)
{
	if (!FilterSprite::init())
		return false;

	m_colorType = color;

	//加载箱子
	this->initWithFile(StringUtils::format("images/chest/chest_diamond_open%d.png", m_colorType));

	this->setAnchorPoint(Vec2(0, 0));		// 设置锚点为左下角

	return true;
}
