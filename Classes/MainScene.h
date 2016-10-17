// MainScene.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"

class MainScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(MainScene);

private:
	virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event);
	virtual void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unused_event);

private:
	// UI�����¼�
	void onSettingsBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);		// ���ð�ť�����
	void onCardBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);			// ��Ƭ��������ť�����
	void onAddJewelBtnClick(Ref * pSender, cocos2d::ui::TouchEventType type);		// ��ʯ��ť�����
private:
	// ��
	cocos2d::Sprite * m_zergling;
	//���估�䶯��
	cocos2d::Sprite * chest_sprite;
	cocos2d::Animate* createAnimate();

	// ��ǩ�Ͱ�ť�ͽ�����
	cocos2d::ui::Text * m_jewelText;
	cocos2d::ui::Text * m_energyText;
	cocos2d::ui::Text * m_scoreText;
	cocos2d::ui::Button * m_settingsBtn;
	cocos2d::ui::Button * m_cardBtn;
	cocos2d::ui::Button * m_addJewelBtn;
	cocos2d::ui::LoadingBar * m_energyBar;
};