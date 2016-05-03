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
	if (!Sprite::init())
	{
		return false;
	}
	this->initWithFile("SCs_SCV_C_01.PNG");
	this->setScale(0.5f);
	this->setAnchorPoint(Vec2(0, 0));// 设置锚点为左下角
	return true;
}
void Farmer::tapped()
{
	this->removeFromParent();
}