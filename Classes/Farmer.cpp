//Farmer.cpp
#include"Farmer.h"
USING_NS_CC;

Farmer* Farmer::FarmerAppear(int type)
{
	auto farmer = new Farmer();

	if (farmer && farmer->init(type))
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

bool Farmer::init(int type)
{
	if (!Sprite::init())
	{
		return false;
	}
	switch (type)
	{
	case 1:
		this->initWithFile("Res/Workers/SCs_SCV_C_01.PNG");
		break;
	case 2:
		this->initWithFile("Res/Workers/SCs_Drone_C_01.PNG");
		break;
	case 3:
		this->initWithFile("Res/Workers/SCs_Probe_C_01.PNG");
			break;
	default:
		break;
	}
	
	//this->setScale(0.5f);
	this->setAnchorPoint(Vec2(0, 0));// 设置锚点为左下角
	return true;
}
void Farmer::tapped()
{
	this->removeFromParent();
}