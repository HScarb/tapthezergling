#ifndef __RUNSCENE_H__
#define __RUNSCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "TollgateControlLayer.h"
#include "Box2D\Box2D.h"

class RunScene : public cocos2d::Layer
{
public:
	virtual bool init(int diff, int loop);
	b2World * world;
	//virtual bool init();
	// CREATE_FUNC(RunScene);			//��һ�д��������⣬��ȷ��ʾ��ǰ����Layer��init�ǿղ�����

	static cocos2d::Scene * createScene(int diff, int loop);
	static cocos2d::Layer * create(int diff, int loop);
	
	void setRun();
	//�����������
	virtual void onEnter();
	void getPosition(float dt);
	/*float getMeteorPositionX(Sprite *sp);
	float getMeteorPositionY(Sprite *sp);*/

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);


private:
	TollgateControlLayer * m_controlLayer;

private: 
	float Position_x0, Position_x1, Position_x2, Position_x3;	//������Ԫ�صĸ���λ��
	float Position_y0, Position_y1, Position_y2, Position_y3;
	bool m_isRunning;
	cocos2d::Sprite * m_zeriling_sprite;
	cocos2d::Sprite * m_meteorolite;
	cocos2d::Sprite * m_meteorolite2;
	cocos2d::Sprite * m_meteorolite3;
	cocos2d::ui::Button * m_pauseBtn;
	cocos2d::ui::Text * m_timeText;
	cocos2d::ui::LoadingBar* m_timeBar;

	cocos2d::Animate * createAnimate();
};

/*WOW������Ч��*/
class FlowWord : public cocos2d::Node 
{
public:
	static FlowWord* create();
	bool init();

public:
	void showWord(const char* text, cocos2d::Vec2 pos);
private:
	cocos2d::LabelTTF* m_textLab;

	void flowEnd();
};

#endif 



