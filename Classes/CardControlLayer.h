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

	virtual void update(float dt) override;
	//ɾ����Ƭ
	void DeleteACard(Card * card);
	//�ӿ�Ƭ�ϳ�����ɾ����Ƭ
	void DeleteAcardFromEnhancer(Card * card);
	//׼���ƶ�ȥ�ϳ�
	void MoveCardIntoEnhancer(Card *card);
	//��ʾ��Ƭ
	void showCards();
	//����ڿ�Ƭ�ϳ����е�δ�ںϳ�ʱ�Ŀ�Ƭ����ʹ��Ƭ�ص��ײ���Ƭ��Ŵ�
	void ClickCardBackToBottom(Card * card);
	//����ϳ������Ѿ��п�Ƭ���ǾͰ�����Ҫ�ƶ��Ŀ�Ƭ�������е� ��Ƭ���бȽ�
	bool IsTheSameCardInEnhancer(Card * card);
	//��⵱ǰҪ�ƶ��Ŀ�Ƭ�ڿ�Ƭ����������Ƿ�Ϊ����
	bool IsSingleInVector(Card * card);

	//���ӿ�Ƭ�ϳɳɹ���Ļص�����
	void cardEnhanceSucceedCallBack(cocos2d::EventCustom * cardEvent);
	//��ȡʱ���
	int getTimeStamp();
	//��ȡ��ǰʱ��
	time_t getCurrentTime();

	// �ռ��ϳɺõĿ�Ƭ
	void collectEnhancedCard(Card* card);

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
private:
	//��ȡ���س�ʼ����ǰλ�úʹ��ؽ�������
	cocos2d::Vec2 m_beginPos, m_delta, m_endPos, m_movedPos;
	//��Ƭ��Ϣ��
	CardInfoLayer * m_cardInfoLayer;
	//��Ļ�ֱ���
	cocos2d::Size m_frameSize;
	// ��ǰҪ�ƶ��Ŀ�Ƭ
	Card * m_operatingCard;
	//�ϳ������Ƿ��п�Ƭ
	bool m_isEnhancerContaninsACard;
	//���Ҫ�ƶ��Ŀ�Ƭ�Ƿ�Ϊ����
	bool m_isSingleCard;
	//�Ƿ��п�Ƭ�Ѿ��ϳ����
	bool m_isCollectionContainsCard;
	//�Ƿ��п�Ƭ���ںϳ�
	bool m_isCardsStartEnhance;
	cocos2d::ui::Text * m_cardEnhanceTime;
	//cocos2d::ui::ImageView * m_sprite;
	//��ȡ��ǰʱ���ʱ������룩
	int m_timeStamp;
	time_t m_currentTime;
	float m_deltaX;
};