//CardControlLayer.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "Card.h"
#include "CardInfoLayer.h"

class CardControlLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init() override;
	CREATE_FUNC(CardControlLayer);

	/*void showLayer();			// 显示卡片控制层，创建禁止触摸层
	void unShowLayer();			// 不现实卡片控制层，销毁禁止触摸层*/

	//增加卡片
	void CreateACard(int info,int level,int posX);
	//删除卡片
	void DeleteACard(Card * card);
	//准备移动去合成
	void MoveCardIntoEnhancer(Card *card);
	//通过卡片信息，等级往容器中增加卡片
	Card * CreateACardByTypeAndLevel(Card::CardInfo info, int level,int posX);
	//显示卡片
	void showCards();
	//卡片合成后生成存放
	void CardAfterEnhancer(Card * card);
	//点击在卡片合成器中的未在合成时的卡片可以使卡片回到底部卡片存放处
	void ClickCardBackToBottom(Card * card);
	//如果合成器中已经有卡片，那就把现在要移动的卡片和容器中的 卡片进行比较
	bool IsTheSameCardInEnhancer(Card * card);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	void onCloseBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onCollectBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
private:
	//按钮
	cocos2d::ui::Button * m_collectBtn;
	cocos2d::ui::Button * m_closeBtn;
	/*// 禁止触摸层
	NoTouchLayer * m_noTouchLayer;*/
private:
	//卡片容器
	cocos2d::Vector<Card*> m_CardMsg;
	cocos2d::Vector<Card*> m_CardBeforeEnhancer;
	cocos2d::Vector<Card*> m_CardAfterEnhancer;
	/*//加载滑动容器
	cocos2d::ui::ScrollView * m_cardView;*/
	cocos2d::Vec2 m_beginPos, m_delta, m_endPos, m_movedPos;

	//卡片信息层
	CardInfoLayer * m_cardInfoLayer;
	//屏幕分辨率
	cocos2d::Size m_frameSize;
	Card * m_operatingCard;
	//计算要移动的卡片在卡片容器中和合成器中的数目之和
	int m_sameCardsInVector;
	//合成器中是否有卡片
	bool m_isEnhancerContaninsACard;
	//检测要移动的卡片是否为单张
	bool m_isSingleCard;
};