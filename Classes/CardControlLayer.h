//CardControlLayer.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "NoTouchLayer.h"
#include "CardControlLayer.h"

class CardControlLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init() override;
	CREATE_FUNC(CardControlLayer);

	Sprite * CreateACard();
	void showLayer();			// ÏÔÊ¾¿¨Æ¬¿ØÖÆ²ã£¬´´½¨½ûÖ¹´¥Ãþ²ã
	void unShowLayer();			// ²»ÏÖÊµ¿¨Æ¬¿ØÖÆ²ã£¬Ïú»Ù½ûÖ¹´¥Ãþ²ã

	cocos2d::ui::ScrollView * m_cardView;
	Layer * m_cardContainer;

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	void onCloseBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onCollectBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
private:
	//°´Å¥
	cocos2d::ui::Button * m_collectBtn;
	cocos2d::ui::Button * m_closeBtn;
	// ½ûÖ¹´¥Ãþ²ã
	NoTouchLayer * m_noTouchLayer;
	Vector<Sprite*>m_cardMsg;
};