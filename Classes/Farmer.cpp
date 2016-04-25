//Farmer.cpp
#include"Farmer.h"
USING_NS_CC;
Farmer* Farmer::FarmerAppear(Farmerappear appear)
{
	auto farmer = new Farmer();

	if (farmer && farmer->init(appear))
	{
		farmer->autorelease();
		return farmer;
	}
	else
	{
		CC_SAFE_DELETE(farmer);
		return nullptr;
	}
}

bool Farmer::init(int appear)
{
	if (!FilterSprite::init())
	{
		return false;
	}
	m_appear = appear;
	//Sprite *farmer = Sprite::create("SCs_Zergling_C3_02.png");
	this->initWithFile(StringUtils::format("Res/zergling_small_%d.png", m_appear));
	this->setAnchorPoint(Vec2(0, 0));
	return true;
}
void Farmer::tapped()
{
	this->removeFromParent();
}