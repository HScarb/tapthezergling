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

	void showLayer();			// ��ʾ��Ƭ���Ʋ㣬������ֹ������
	void unShowLayer();			// ����ʵ��Ƭ���Ʋ㣬���ٽ�ֹ������

	//���ӿ�Ƭ
	void CreateACard(int info,int level);
	//ɾ����Ƭ
	void DeleteACard(Card * card);
	//ͨ����Ƭ��Ϣ���ȼ������������ӿ�Ƭ
	Card * CreateACardByTypeAndLevel(Card::CardInfo info, int level);
	
	//��ʾ��Ƭ
	void showCards();

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	void testMenuEvent(Ref * sender);
private:
	void onCloseBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onCollectBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
private:
	//��ť
	cocos2d::ui::Button * m_collectBtn;
	cocos2d::ui::Button * m_closeBtn;
	// ��ֹ������
	NoTouchLayer * m_noTouchLayer;
private:
	//��Ƭ����
	Vector<Card*> m_CardMsg;
	//���ػ�������
	cocos2d::ui::ScrollView * m_cardView;
};