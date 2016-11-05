//CardControlLayer.cpp
#include"CardControlLayer.h"
#include "cocostudio/CocoStudio.h"
#include "CardManager.h"

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
	this->addChild(ui,1);

	//��ui�м��ذ�ť
	m_closeBtn = (Button *)ui->getChildByName("Button_x");
	m_collectBtn = (Button *)ui->getChildByName("Button_collect");
	//��ui�м��ؿ�Ƭ������ͼ
	m_cardView = (ScrollView *)ui->getChildByName("cardView");
	//����manager��Ŀ�Ƭ����
	m_CardMsg = CardManager::getInstance()->getAllCards();
	if (m_CardMsg.size() == 0)
	{
		//������Ƭ
		for (int i = 10; i >= 1; i--)
		{
			CreateACard(i, 1);
		}
	}
	CreateACard(5, 2);
	//CardManager::getInstance()->DeleteCardByTypeAndLevel(5, 1);
	CardManager::getInstance()->SortCardMsg();
	//��ʾ��Ƭ
	showCards();

	// ͼƬ�˵������
	// ����һ��ͼƬ�˵����һ�������Ǳ�����ͼƬ���ڶ��������ǰ��º��ͼƬ��Ȼ����һ���ص�������ע������ص�������Ҫ��һ������
	MenuItemImage* testMenuItem = MenuItemImage::create("Res/Cards/Card_1.png", "Res/Cards/Card_2.png", CC_CALLBACK_1(CardControlLayer::testMenuEvent, this));
	// �����˵���������԰Ѷ���˵������һ���˵�����create���� create(testMenuItem, item2, item3, NULL) ע����NULL��β
	Menu* p_menu = Menu::createWithItem(testMenuItem);
	// ���˵�����ScrollView
	m_cardView->addChild(p_menu);

	//���ؼ���
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CardControlLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(CardControlLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	m_closeBtn->addTouchEventListener(this, toucheventselector(CardControlLayer::onCloseBtnClick));
	m_collectBtn->addTouchEventListener(this, toucheventselector(CardControlLayer::onCollectBtnClick));
	return true;

}

void CardControlLayer::CreateACard(int info,int level)
{
	CardManager::getInstance()->InsertACard(CreateACardByTypeAndLevel(
		(Card::CardInfo)info, level));
}

void CardControlLayer::DeleteACard(Card* card)
{
	card->removeFromParent();
	CardManager::getInstance()->DeleteCardByTypeAndLevel(card->getCardinfo(), card->getCardLevel());
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
	// ����һ���޴����㣬�ڿ�Ƭ���Ʋ������
	m_noTouchLayer = NoTouchLayer::create();
	this->addChild(m_noTouchLayer, 0);
	// ��ʾ��Ƭ���Ʋ�
	this->setVisible(true);
}

void CardControlLayer::unShowLayer()
{
	// �Ƴ��޴�����
	this->removeChild(m_noTouchLayer);
	// ���ؿ�Ƭ���Ʋ�
	this->setVisible(false);
}

Card* CardControlLayer::CreateACardByTypeAndLevel(Card::CardInfo info, int level)
{
	Card * card = nullptr;
	if (info == 0)
		return nullptr;
	card = Card::createByInfo(info);
	card->setCardLevel(level);			//���õȼ�
	return card;
}

void CardControlLayer::showCards()
{
	auto cards = CardManager::getInstance()->getAllCards();
	int i = 0;
	for (auto card : cards)
	{
		if (card->getCardinfo() == 5 && card->getCardLevel() == 1)
		{
			DeleteACard(card);
			continue;
		}
		card = CreateACardByTypeAndLevel((Card::CardInfo)card->getCardinfo(), card->getCardLevel());
		log("Card Type %d,Card Level %d", card->getCardinfo(), card->getCardLevel());
		card->setPosition(i * 80, 200);
		m_cardView->addChild(card);
		i++;
	}
}

bool CardControlLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
/*	auto cards = CardManager::getInstance()->getAllCards();
	Rect rect;
	int i;
	for (auto card : cards)
	{
		rect = card->getBoundingBox();
		i = card->getCardinfo();
		auto pos = touch->getLocation();
		if (rect.containsPoint(pos))
		{
			log("cardtype%d", i);
		}
	}
	log("12345");*/
	return true;
}

void CardControlLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	
}

void CardControlLayer::testMenuEvent(Ref * sender)
{
	log("Menu touched");
}