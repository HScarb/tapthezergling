// FilterSample.h
#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
// #include "ExtensionMacros.h"
#include "VisibleRect.h"
#include "filters/cocos2dFilters.h"

USING_NS_CC_EXT;

typedef enum
{
	LEFT_TOP,
	RIGHT_TOP,
	LEFT_BOTTOM,
	RIGHT_BOTTOM,
	CENTER,
}ccLocation;

class FilterSample : public cocos2d::Layer
{
public:
	static cocos2d::Scene * scene();

	FilterSample();
	~FilterSample();

	virtual bool init();

	void onClose(Ref * pSender);

	void onRestart(Ref * pSender);
	void onNext(Ref * pSender);
	void onBack(Ref * pSender);
	void onClearFilter(Ref * pSender);

	Sprite * getFilteredSprite(int index);

	CREATE_FUNC(FilterSample);

	virtual void update(float delta);

private:
	Label * _nameLabel;
	Filters _filters;
	std::vector<std::string> _filterNames;
	std::vector<Filters> _multiFilters;
	std::vector<std::string> _multiFilterNames;
	int _filtersNum = 0;
	Node * _pNode;

	void initFilters();
	void showFilteredDisplay(int index);

	Sprite * testFilter(Filter * filter, ccLocation location = CENTER,
		int order = 0, const char * path = "helloworld.png");
	Sprite * testFilter(Filters filters, ccLocation location = CENTER,
		int order = 0, const char * path = "helloworld.png");
	Sprite * testFilterFromFrame(Filter * filter, ccLocation location = CENTER,
		int order = 0, const char * path = "grass.png");
	Sprite * testFIlterFromFrame(Filters filters, ccLocation location = CENTER,
		int order = 0, const char * path = "grass.png");
	Vec2 getLocation(ccLocation location);

private:
	GLProgram * getEmboss();
	cocos2d::GLProgram * getEmbossMov();
	cocos2d::GLProgram * getColorRamp();
	cocos2d::GLProgram * getGrass();

	int _timeUnifromLocation;
	float _totalTime = 0.0f;
};