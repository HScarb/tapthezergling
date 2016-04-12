//EacCandiesScnen.cpp
#include "EatCandiesScene.h"
#include "cocos2d.h"
USING_NS_CC;

EatCandiesScene* EatCandiesScene::createByType(int type)
{
	auto candies = new EatCandiesScene();

	if (candies && candies->init(type))
		{
			candies->autorelease();
			return candies;
		}
	else
		{
			CC_SAFE_DELETE(candies);
			return nullptr;
		}
}

bool EatCandiesScene::init(int type)
{
	Sprite::init();

	m_type = type;
	m_x = random(100,300);
	m_y = random(100,300);

	m_isCrushing = false;

	char name[2] = { 0 };//初始化纹理图片
	sprintf(name, "SCs_DancingFlowers_00", m_type);
	this->initWithTexture(TextureCache::getInstance()->getTextureForKey(name));

	return true;
}

void EatCandiesScene::crush()
{
	//开始消除，消除状态为真，直到消除动作结束，将宝石移除渲染节点，并置消除状态为假
	m_isCrushing = true;
	auto action = FadeOut::create(0.2);
	auto call = CallFunc::create([this](){
		this->removeFromParent();
		m_isCrushing = false;
	});
	this->runAction(Sequence::create(action, call, nullptr));

}






	



