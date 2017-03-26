#include "cocos2d.h"
#include "FilterSprite.h"

class Meteorolite : public cocos2d::Sprite
{
public:
	Meteorolite();
	virtual bool init();
	void show();             //显示陨石	
	void hide();			//隐藏陨石
	void reset();			//重置陨石
	void speed();			//陨石下降速度提升
	bool isAlive();         //是否活动

	void create();			//创建陨石
	void destroy();			//摧毁陨石

private:
	bool m_isAlive;
	cocos2d::Sprite * thing;

};