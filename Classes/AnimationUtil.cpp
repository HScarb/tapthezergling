// AnimationUtil.cpp
#include "AnimationUtil.h"
USING_NS_CC;

Animation* AnimationUtil::createWithSingleFrameName(const char* iName, float delay, int iLoops, bool restoreOriginalFrame)
{
	SpriteFrameCache * cache = SpriteFrameCache::getInstance();
	TextureCache * textureCache = TextureCache::getInstance();

	Vector<SpriteFrame*> frameVec;
	SpriteFrame * frame = nullptr;

	int index = 1;

	do
	{
		auto texture = textureCache->getTextureForKey(StringUtils::format("%s%d.png", iName, index));
		frame = SpriteFrame::createWithTexture(texture, 
			Rect(0, 0, texture->getPixelsWide(), 
				texture->getPixelsHigh()));
		
		if (frame == nullptr)
			break;
		frameVec.pushBack(frame);
	} while (true);

	Animation * animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(iLoops);
	animation->setDelayPerUnit(delay);
	animation->setRestoreOriginalFrame(restoreOriginalFrame);

	return animation;
}

Animation* AnimationUtil::createWithFrameNameAndNum(const char* iName, int iNum, float delay, int iLoops, bool restoreOriginalFrame)
{
	SpriteFrameCache * cache = SpriteFrameCache::getInstance();
	TextureCache * textureCache = TextureCache::getInstance();

	Vector<SpriteFrame*> frameVec;
	SpriteFrame * frame = nullptr;

	for (int i = 1; i <= iNum;i++)
	{
		auto texture = textureCache->getTextureForKey(StringUtils::format("%s%d.png", iName, i));
		frame = SpriteFrame::createWithTexture(texture,
			Rect(0, 0, texture->getPixelsWide(),
				texture->getPixelsHigh()));
		frameVec.pushBack(frame);
	}

	Animation * animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(iLoops);
	animation->setDelayPerUnit(delay);
	animation->setRestoreOriginalFrame(restoreOriginalFrame);

	return animation;
}