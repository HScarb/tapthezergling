// GlobalDefine.h
#pragma once

// 1 - convenience measurements
#define SCREEN Director::getInstance()->getWinSize()
#define CENTER Vec2(SCREEN.width / 2, SCREEN.height / 2)
#define TEXTURECACHE TextureCache::getInstance()
#define CURTIME do {                                                        \
    timeval time;                                                           \
    gettimeofday(&time, NULL);                                              \
    unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000); \
    return (float)millisecs;                                                \
} while (0)
#define PLAY_BURST_ANIMATION(__POS__, __SCALE__) \
{ \
	Sprite * virtualBurstSprite = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("star crafts/starcrafts_SmallUnit_Death_1.png")); \
	virtualBurstSprite->setScale(__SCALE__); \
	virtualBurstSprite->setPosition(__POS__); \
	this->addChild(virtualBurstSprite); \
	auto burst = AnimationUtil::createWithFrameNameAndNumRange("star crafts/starcrafts_SmallUnit_Death_", 1, 10, 1 / 12.0, 1, true); \
	auto unShow = CallFunc::create([virtualBurstSprite]() {virtualBurstSprite->removeFromParent(); }); \
	virtualBurstSprite->runAction(Sequence::create(Animate::create(burst), unShow, nullptr)); \
}

// 2 - file path
	// units
#define PATH_SCV_SMALL "Units/scv_small.png"
#define PATH_DRONE_SMALL "Units/drone_small.png"
#define PATH_PROBE_SMALL "Units/probe_small.png"
#define PATH_ZERGLING_SMALL "Units/zergling_small.png"
#define PATH_MARINE_SMALL "Units/marine_small.png"
#define PATH_MARAUDER_SMALL "Units/marauder_small.png"
#define PATH_OVERLORD_SMALL "Units/overlord_small.png"
#define PATH_ROACH_SMALL "Units/roach_small.png"
#define PATH_ZEALOT_SMALL "Units/zealot_small.png"
#define PATH_STALKER_SMALL "Units/stalker_small.png"
	// buildings
#define PATH_ZERG_BASE "star crafts/SCs_Hatchery_C.png"
#define PATH_TERRAN_BASE "star crafts/SCs_CommandCenter_C.png"
#define PATH_PROTOSS_BASE "star crafts/SCs_Nexus_C.png"
#define PATH_SPAWNINGPOOL "star crafts/SCs_SpawningPool_C.png"
	// pics
#define PATH_BUTTON_ACCEPT_1 "RESOURCE/button_accept_1.png"
#define PATH_BUTTON_ACCEPT_2 "RESOURCE/button_accept_2.png"
#define PATH_ADD_TWO "RESOURCE/add_two.png"
