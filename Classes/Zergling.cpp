// Zergling.cpp
#include "Zergling.h"
USING_NS_CC;

Zergling* Zergling::createByColor(ZerglingColor color)
{
	auto zergling = new Zergling();

	if(zergling && zergling->init(color))
	{
		zergling->autorelease();
		return zergling;
	}
	else
	{
		CC_SAFE_DELETE(zergling);
		return nullptr;
	}
}

bool Zergling::init(int color)
{
	if (!FilterSprite::init())
		return false;

	m_colorType = color;

	// ������Դ�����ز�ͬ��ɫ�Ĺ�
	// this->initWithTexture(Texture2D::, Rect::ZERO);
	this->initWithFile(StringUtils::format("Res/zergling_small_%d.png", m_colorType));

	this->setAnchorPoint(Vec2(0, 0));		// ����ê��Ϊ���½�

	return true;
}

void Zergling::eatAnimation()
{
	// play eat animation
}

void Zergling::tapped()
{
	this->removeFromParent();
}