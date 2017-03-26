#include "cocostudio/CocoStudio.h"
#include "FreeCardLayer.h"
#include "Global.h"

USING_NS_CC;
using namespace ui;

cocos2d::Scene* FreeCardLayer::createScene(int info)
{
	auto scene = Scene::create();
	auto layer = FreeCardLayer::create(info);
	scene->addChild(layer);
	return scene;
}

bool FreeCardLayer::init(int info)
{
	if(!Layer::init())
	{
		return false;
	}
	m_claimBtn = nullptr;

	auto ui = CSLoader::createNode("FreeCardLayer.csb");

	m_claimBtn = (Button*)ui->getChildByName("Button_claim");
	m_cardName = (Text*)ui->getChildByName("cardName");

	// ´¥¿Ø¼àÌý£¬ÍÌ²¢´¥¿Ø
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(FreeCardLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	m_claimBtn->addTouchEventListener(this, toucheventselector(FreeCardLayer::onClaimBtnClick));

	// ÏÔÊ¾¿¨Æ¬ÐÅÏ¢
	m_cardName->setText(CARD_NAME[info]);

	// ÏÔÊ¾¿¨Æ¬
	m_card = Card::createByLevelAndInfo(1, info);
	m_card->setPosition(440.0, 340.0);
	ui->addChild(m_card);

	this->addChild(ui);

	return true;
}

FreeCardLayer* FreeCardLayer::create(int info)
{
	auto bRet = new FreeCardLayer();
	if(bRet && bRet->init(info))
	{
		bRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(bRet);
	}
	return bRet;
}

void FreeCardLayer::onClaimBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if(type == TOUCH_EVENT_ENDED)
	{
		this->removeFromParent();
	}
}