/****************************************************************************

FilterSpirte.h

Created by LiaoYanXuan  on 14-10-21.
****************************************************************************/

#ifndef __FilterSpirte_h
#define __FilterSpirte_h

#include "cocos2d.h"

class FilterSprite : public cocos2d::Sprite {

public:

	FilterSprite();
	virtual ~FilterSprite();

	static FilterSprite* create();
	static FilterSprite* create(const std::string& filename);
	static FilterSprite* create(const std::string& filename, const cocos2d::Rect& rect);


	static FilterSprite* createWithTexture(cocos2d::Texture2D *pTexture);
	static FilterSprite* createWithTexture(cocos2d::Texture2D *pTexture, const cocos2d::Rect& rect, bool rotated = false);
	static FilterSprite* createWithSpriteFrame(cocos2d::SpriteFrame *pSpriteFrame);
	static FilterSprite* createWithSpriteFrameName(const std::string& spriteFrameName);

	bool initWithTexture(cocos2d::Texture2D* pTexture, const cocos2d::Rect& tRect);
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
	void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);
	void setFilterMat(cocos2d::Mat4 matrixArray);
	//to-do 提供一个设置滤镜的方法
protected:
	cocos2d::CustomCommand _customCommand;
private:
	cocos2d::Mat4   m_uSpriteFilter;
};

#endif