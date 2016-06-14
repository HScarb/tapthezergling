//Farmer.cpp
#include"Farmer.h"
#include "Global.h"
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
		this->initWithFile(PATH_SCV_SMALL);
		break;
	case 2:
		this->initWithFile(PATH_DRONE_SMALL);
		break;
	case 3:
		this->initWithFile(PATH_PROBE_SMALL);
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