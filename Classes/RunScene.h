#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "TollgateControlLayer.h"

class RunScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene(int diff, int loop);
	virtual bool init(int diff, int loop);	
	static cocos2d::Layer * create(int diff, int loop);
	
	void setRun();

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);

private:
	TollgateControlLayer * m_controlLayer;

private: 
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

/*WOW£¡¶¯»­Ð§¹û*/
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




