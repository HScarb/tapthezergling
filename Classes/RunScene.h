#ifndef __RUNSCENE_H__
#define __RUNSCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "TollgateControlLayer.h"
#include "Box2D\Box2D.h"

USING_NS_CC;

#define RED_BIT_MASK		0x4
#define GREEN_BIT_MASK     0x2
#define BLUE_BIT_MASK	    0x1
#define EDGE_BIT_MASK    0x8

class RunScene : public cocos2d::Layer
{
public:
	virtual bool init(int diff, int loop);
	b2World * world;
	//virtual bool init();
	// CREATE_FUNC(RunScene);			//这一行代码有问题，正确显示的前提是Layer的init是空参数的

	static cocos2d::Scene * createScene(int diff, int loop);
	static cocos2d::Layer * create(int diff, int loop);
	
	void setRun();
	//物理引擎入口
	virtual void onEnter();
	void getPosition(float dt);
	/*float getMeteorPositionX(Sprite *sp);
	float getMeteorPositionY(Sprite *sp);*/

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);


private:
	TollgateControlLayer * m_controlLayer;

private: 
	float Position_x0, Position_x1, Position_x2, Position_x3;	//代表了元素的各个位置
	float Position_y0, Position_y1, Position_y2, Position_y3;
	bool m_isRunning;
	cocos2d::Sprite * m_zeriling_sprite;
	cocos2d::Sprite * m_meteorolite;
	cocos2d::Sprite * m_meteorolite2;
	cocos2d::Sprite * m_meteorolite3;
	cocos2d::ui::Button * m_pauseBtn;
	cocos2d::ui::Text * m_timeText;
	cocos2d::ui::LoadingBar* m_timeBar;

	cocos2d::Animate * m_createAnimate();
};

/*WOW！动画效果*/
class FlowWord : public CCNode 
{
public:
	static FlowWord* create();
	bool init();

public:
	void showWord(const char* text, CCPoint pos);
private:
	CCLabelTTF* m_textLab;

	void flowEnd();
};

#endif 



