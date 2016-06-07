//Worker.cpp
#include"Worker.h"
USING_NS_CC;

Worker* Worker::Workertype(int type)
{
	auto worker = new Worker();
	if (worker&& worker->init(type))
	{
		worker->autorelease();
		return worker;
	}
	else
	{
		CC_SAFE_DELETE(worker);
		return nullptr;
	}
}

bool Worker::init(int type)
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
	case 7:
		this->initWithFile("Res/zergling_small_7.png");
		this->setScale(0.9f);
		break;
	default:
		break;
	}
	this->setAnchorPoint(Vec2(0, 0));// 设置锚点为左下角
	return true;
}

void Worker::tapped()
{
	this->removeFromParent();
}