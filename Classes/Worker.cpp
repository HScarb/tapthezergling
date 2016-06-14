//Worker.cpp
#include"Worker.h"
#include "Global.h"
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
		this->initWithFile(PATH_SCV_SMALL);
		break;
	case 2:
		this->initWithFile(PATH_DRONE_SMALL);
		break;
	case 3:
		this->initWithFile(PATH_PROBE_SMALL);
		break;
	case 7:
		this->initWithFile("zergling_small_7.png");
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