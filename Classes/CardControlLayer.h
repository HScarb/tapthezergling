//CardControlLayer.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "NoTouchLayer.h"
#include "Card.h"

class CardControlLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init() override;
	CREATE_FUNC(CardControlLayer);

	void showLayer();			// 显示卡片控制层，创建禁止触摸层
	void unShowLayer();			// 不现实卡片控制层，销毁禁止触摸层

	//增加卡片
	void CreateACard(int info,int level);
	//删除卡片
	void DeleteACard(Card * card);
	//通过卡片信息，等级往容器中增加卡片
	Card * CreateACardByTypeAndLevel(Card::CardInfo info, int level);
	
	//显示卡片
	void showCards();

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	void testMenuEvent(Ref * sender);
private:
	void onCloseBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onCollectBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
private:
	//按钮
	cocos2d::ui::Button * m_collectBtn;
	cocos2d::ui::Button * m_closeBtn;
	// 禁止触摸层
	NoTouchLayer * m_noTouchLayer;
private:
	//卡片容器
	Vector<Card*> m_CardMsg;
	//加载滑动容器
	cocos2d::ui::ScrollView * m_cardView;
};