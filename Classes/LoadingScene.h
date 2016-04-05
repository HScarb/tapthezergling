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
	void onTextureLoading(float dt);		// 检测图片是否加载完毕

	int m_texture_num;						// 当前加载的图片数
	float m_total_time;
};