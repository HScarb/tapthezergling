#include "farmerandflower.h"
#include "Global.h"
USING_NS_CC;

farmerandflower* farmerandflower::createByType(int type)
{
	auto flower = new farmerandflower();

	if (flower && flower->initByType(type))
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

bool farmerandflower::initByType(int color)
{
	if (!Sprite::init())
		return false;

	m_colorType = color;

	switch (color)
	{
	case NONE:
		return false;
	case SCV:
		if (!Sprite::initWithTexture(TextureCache::getInstance()->getTextureForKey(PATH_SCV_SMALL)))
			return false;
		break;
	case Drone:
		if (!Sprite::initWithTexture(TextureCache::getInstance()->getTextureForKey(PATH_DRONE_SMALL)))
			return false;
		break;
	case Probe:
		if (!Sprite::initWithTexture(TextureCache::getInstance()->getTextureForKey(PATH_PROBE_SMALL)))
			return false;
		break;
	case Zergling:
		if (!Sprite::initWithTexture(TextureCache::getInstance()->getTextureForKey(PATH_ZERGLING_SMALL)))
			return false;
		break;
	case Marine:
		if (!Sprite::initWithTexture(TEXTURECACHE->getTextureForKey(PATH_MARINE_SMALL)))
			return false;
		break;
	case Marauder:
		if (!Sprite::initWithTexture(TEXTURECACHE->getTextureForKey(PATH_MARAUDER_SMALL)))
			return false;
		break;
	case Overlord:
		if (!Sprite::initWithTexture(TEXTURECACHE->getTextureForKey(PATH_OVERLORD_SMALL)))
			return false;
		break;
	case Roach:
		if (!Sprite::initWithTexture(TEXTURECACHE->getTextureForKey(PATH_ROACH_SMALL)))
			return false;
		break;
	case Zealot:
		if (!Sprite::initWithTexture(TEXTURECACHE->getTextureForKey(PATH_ZEALOT_SMALL)))
			return false;
		break;
	case Stalker:
		if (!Sprite::initWithTexture(TEXTURECACHE->getTextureForKey(PATH_STALKER_SMALL)))
			return false;
		break;
	default: break;
	}

	this->setAnchorPoint(Vec2(0.5, 0.5));		// 设置锚点为左下角

	return true;
}

void farmerandflower::eatAnimation()
{

}

void farmerandflower::tapped()
{
	this->removeFromParent();
}

