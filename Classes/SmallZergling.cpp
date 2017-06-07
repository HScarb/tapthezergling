// SmallZergling.cpp
#include "SmallZergling.h"
#include "AnimationUtil.h"
USING_NS_CC;

bool SmallZergling::init()
{
//	if (!Sprite::initWithTexture(TextureCache::getInstance()->getTextureForKey("Res\zergling\SCs_Zergling_C3_04.png")))
//		return false;
	if (!Sprite::initWithFile("zergling/SCs_Zergling_C3_04.png"))
		return false;

	auto idleAnimation = AnimationUtil::createWithFrameNameAndNumRange("res/zergling/SCs_Zergling_C3_", 44, 48, 1.0 / 12.0, -1,true);
	this->setIdleAction(RepeatForever::create(Animate::create(idleAnimation)));
	auto runAnimation = AnimationUtil::createWithFrameNameAndNumRange("res/zergling/SCs_Zergling_C3_", 33, 36, 1.0 / 12.0, 1, true);
	this->setRunAction(Animate::create(runAnimation));

	return true;
}

void SmallZergling::idle()
{
	this->stopAllActions();
	this->runAction(_idleAction);
}

void SmallZergling::run()
{
	this->stopAllActions();
	this->runAction(_runAction);
}