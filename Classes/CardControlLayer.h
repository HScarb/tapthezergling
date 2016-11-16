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

	/*void showLayer();			// ��ʾ��Ƭ���Ʋ㣬������ֹ������
	void unShowLayer();			// ����ʵ��Ƭ���Ʋ㣬���ٽ�ֹ������*/

	//���ӿ�Ƭ
	void CreateACard(int info,int level,int posX);
	//ɾ����Ƭ
	void DeleteACard(Card * card);
	//׼���ƶ�ȥ�ϳ�
	void MoveCardIntoEnhancer(Card *card);
	//ͨ����Ƭ��Ϣ���ȼ������������ӿ�Ƭ
	Card * CreateACardByTypeAndLevel(Card::CardInfo info, int level,int posX);
	//��ʾ��Ƭ
	void showCards();
	//��Ƭ�ϳɺ����ɴ��
	void CardAfterEnhancer(Card * card);
	//����ڿ�Ƭ�ϳ����е�δ�ںϳ�ʱ�Ŀ�Ƭ����ʹ��Ƭ�ص��ײ���Ƭ��Ŵ�
	void ClickCardBackToBottom(Card * card);
	//����ϳ������Ѿ��п�Ƭ���ǾͰ�����Ҫ�ƶ��Ŀ�Ƭ�������е� ��Ƭ���бȽ�
	bool IsTheSameCardInEnhancer(Card * card);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	void onCloseBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onCollectBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
private:
	//��ť
	cocos2d::ui::Button * m_collectBtn;
	cocos2d::ui::Button * m_closeBtn;
	/*// ��ֹ������
	NoTouchLayer * m_noTouchLayer;*/
private:
	//��Ƭ����
	cocos2d::Vector<Card*> m_CardMsg;
	cocos2d::Vector<Card*> m_CardBeforeEnhancer;
	cocos2d::Vector<Card*> m_CardAfterEnhancer;
	/*//���ػ�������
	cocos2d::ui::ScrollView * m_cardView;*/
	cocos2d::Vec2 m_beginPos, m_delta, m_endPos, m_movedPos;

	//��Ƭ��Ϣ��
	CardInfoLayer * m_cardInfoLayer;
	//��Ļ�ֱ���
	cocos2d::Size m_frameSize;
	Card * m_operatingCard;
	//����Ҫ�ƶ��Ŀ�Ƭ�ڿ�Ƭ�����кͺϳ����е���Ŀ֮��
	int m_sameCardsInVector;
	//�ϳ������Ƿ��п�Ƭ
	bool m_isEnhancerContaninsACard;
	//���Ҫ�ƶ��Ŀ�Ƭ�Ƿ�Ϊ����
	bool m_isSingleCard;
};