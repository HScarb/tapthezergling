//Card
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "NoTouchLayer.h"

class CardControlLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init() override;
	CREATE_FUNC(CardControlLayer);

	void showLayer();			// ��ʾ��Ƭ���Ʋ㣬������ֹ������
	void unShowLayer();			// ����ʵ��Ƭ���Ʋ㣬���ٽ�ֹ������
private:
	void onCloseBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onCollectBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);
private:
	//��ť
	cocos2d::ui::Button * m_collectBtn;
	cocos2d::ui::Button * m_closeBtn;
	// ��ֹ������
	NoTouchLayer * m_noTouchLayer;
};