//Card.cpp
#include"CardControlLayer.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* CardControlLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = CardControlLayer::create();
	scene->addChild(scene);
	return scene;
}

bool CardControlLayer::init()
{
	if (!Layer::init())
		return false;

	m_collectBtn = nullptr;
	m_closeBtn = nullptr;
	m_noTouchLayer = nullptr;
	auto ui = CSLoader::createNode("CardEnhancer.csb");
	this->addChild(ui, 1);

	//从ui中加载按钮
	m_closeBtn = (Button *)ui->getChildByName("Button_x");
	m_collectBtn = (Button *)ui->getChildByName("Button_collect");

	m_closeBtn->addTouchEventListener(this, toucheventselector(CardControlLayer::onCloseBtnClick));
	m_collectBtn->addTouchEventListener(this, toucheventselector(CardControlLayer::onCollectBtnClick));
	return true;

}
void CardControlLayer::onCloseBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		unShowLayer();
	}
}
void CardControlLayer::onCollectBtnClick(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	
}

void CardControlLayer::showLayer()
{
	// 创建一个无触摸层，在卡片控制层的下面
	m_noTouchLayer = NoTouchLayer::create();
	this->addChild(m_noTouchLayer, 0);
	// 显示卡片控制层
	this->setVisible(true);
}

void CardControlLayer::unShowLayer()
{
	// 移除无触摸层
	this->removeChild(m_noTouchLayer);
	// 隐藏卡片控制层
	this->setVisible(false);
}