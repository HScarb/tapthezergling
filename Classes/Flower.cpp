#include "Flower.h"
USING_NS_CC;

Flower* Flower::createByColor(FlowerColor color)
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

	// ������Դ�����ز�ͬ��ɫ�Ļ�
	// this->initWithTexture(Texture2D::, Rect::ZERO);
	this->initWithFile(StringUtils::format("Res/flower_%d.png", m_colorType));//��ʱֻ������

	this->setAnchorPoint(Vec2(0, 0));		// ����ê��Ϊ���½�

	return true;
}

void Flower::eatAnimation()
{

}

void Flower::tapped()
{
	this->removeFromParent();
}


