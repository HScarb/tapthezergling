// LoadingScene.h
#pragma once
#include "cocos2d.h"

class LoadingScene : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(LoadingScene);
	static cocos2d::Scene * createScene();

private:
	void onTextureLoading(float dt);		// ���ͼƬ�Ƿ�������

	int m_texture_num;						// ��ǰ���ص�ͼƬ��
	float m_total_time;
};