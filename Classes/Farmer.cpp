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
	if (!Layer::init())
	{
		return false;
	}
	Sprite *farmer = Sprite::create("SCs_Zergling_C3_02.png");
	//farmer->setScale(0.2);
	this->setAnchorPoint(Vec2(0, 0));// 设置锚点为左下角
	this->addChild(farmer);
	return true;
}
void Farmer::tapped()
{
	this->removeFromParent();
}