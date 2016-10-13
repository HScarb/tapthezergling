//Card.cpp
#include"CardCenter.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* CardControl::createScene()
{
	auto scene = Scene::create();
	auto layer = CardControl::create();
	scene->addChild(scene);
	return scene;
}

bool CardControl::init()
{
	if (!Layer::init())
		return false;
	m_collectBtn = nullptr;
	m_closeBtn = nullptr;
	auto ui = CSLoader::createNode("CardEnhancer.csb");
	this->addChild(ui);

	//从ui中加载按钮
	m_closeBtn = (Button *)ui->getChildByName("Button_x");
	m_collectBtn = (Button *)ui->getChildByName("Button_collect");

	m_closeBtn->addTouchEventListener(this, toucheventselector(CardControl::onCloseBtnClick));
	m_collectBtn->addTouchEventListener(this, toucheventselector(CardControl::onCollectBtnClick));
	return true;

}
void CardControl::onCloseBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		setVisible(false);
	}
}
void CardControl::onCollectBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	
}

