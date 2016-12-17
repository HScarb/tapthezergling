// TollgateScene.h
#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "CardControlLayer.h"


class TollgateScene : public cocos2d::Layer
{
public:
	enum RewardType
	{
		None = 0,
		Energy = 1,
		Jewel,
		Card
	};

public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(TollgateScene);

private:
	void runDiamond();      //进行宝石入库动画
	void runEnergy();		//进行能量入库动画
	void runCard();			//进行卡片入库动画
	void addEnergy();		//增加能量值
	void addDiamond();		//增加宝石值
	void setChest();				//创建宝箱和动画
	void addSeconds();				// 增加时间(动画效果)
	void setNextTollgate();			// 随机下一关
	void showNextTollgate();		// 将已经生成的下一关显示出来
	void addSecondsByCard(int info);		//如果卡片容器中有卡片与关卡相对应，就增加关卡时间

	//宝箱和附属精灵及其动画
	cocos2d::Sprite * m_chest_sprite;
	cocos2d::Sprite * m_card_sprite;
	cocos2d::Sprite * m_energy_sprite;
	cocos2d::Sprite * m_diamond_sprite;
	cocos2d::Sprite * m_flash;
	cocos2d::Animate * m_createAnimate();
	cocos2d::Label * m_label;

	void onHomeBtnClicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onGoOnBtnClicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onCardBtnClicked(Ref * pSender, cocos2d::ui::TouchEventType type);

	void onTollgateLabelClicked(Ref * pSender);
	
	void onItem1Clicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onItem2Clicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onItem3Clicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onItem4Clicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onItem5Clicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onItem6Clicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onItem7Clicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onItem8Clicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onItem9Clicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onItem10Clicked(Ref * pSender, cocos2d::ui::TouchEventType type);
	void onItem11Clicked(Ref * pSender, cocos2d::ui::TouchEventType type);

private:
	virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event);
	virtual void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unused_event);

private:
	cocos2d::Label * m_tollgateNumLabel;
	// 标签和按钮和进度条
	cocos2d::ui::Text * m_jewelText;
	cocos2d::ui::Text * m_energyText;
	cocos2d::ui::Button * m_homeBtn;
	cocos2d::ui::Button * m_cardBtn;
	cocos2d::ui::Button * m_addJewelBtn;
	cocos2d::ui::LoadingBar * m_energyBar;
	cocos2d::ui::LoadingBar * m_timeBar;
	cocos2d::ui::Text * m_timeText;
	cocos2d::ui::Text * m_anotherChestText;
	cocos2d::ui::Text * m_congratsText;
	//新加的goon按钮
	cocos2d::ui::Button * m_goOnBtn;

	cocos2d::ui::ScrollView * m_scrollView;

	// 每个关卡的按钮
	cocos2d::ui::Text * m_t1;
	cocos2d::ui::Text * m_t2;
	cocos2d::ui::Text * m_t3;
	cocos2d::ui::Text * m_t4;
	cocos2d::ui::Text * m_t5;
	cocos2d::ui::Text * m_t6;
	cocos2d::ui::Text * m_t7;
	cocos2d::ui::Text * m_t8;
	cocos2d::ui::Text * m_t9;
	cocos2d::ui::Text * m_t10;
	cocos2d::ui::Text * m_t11;
private:
	CardControlLayer * m_cardControlLayer;
};