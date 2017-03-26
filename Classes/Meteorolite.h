#include "cocos2d.h"
#include "FilterSprite.h"

class Meteorolite : public cocos2d::Sprite
{
public:
	Meteorolite();
	virtual bool init();
	void show();             //��ʾ��ʯ	
	void hide();			//������ʯ
	void reset();			//������ʯ
	void speed();			//��ʯ�½��ٶ�����
	bool isAlive();         //�Ƿ�

	void create();			//������ʯ
	void destroy();			//�ݻ���ʯ

private:
	bool m_isAlive;
	cocos2d::Sprite * thing;

};