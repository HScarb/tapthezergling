// FilterSample.cpp
#include "FilterSample.h"
USING_NS_CC;

static int filterIndex = 0;

Scene* FilterSample::scene()
{
	auto scene = Scene::create();
	auto layer = FilterSample::create();
	scene->addChild(layer);
	return scene;
}

FilterSample::FilterSample()
	: _pNode(nullptr)
	, _nameLabel(nullptr)
{}

FilterSample::~FilterSample()
{
	_filters.clear();
}

bool FilterSample::init()
{
	if (!Layer::init())
		return false;
	MenuItemImage * item1 = MenuItemImage::create("b1.png", "b2.png", CC_CALLBACK_1(FilterSample::onBack, this));
	MenuItemImage * item2 = MenuItemImage::create("r1.png", "r2.png", CC_CALLBACK_1(FilterSample::onRestart, this));
	MenuItemImage * item3 = MenuItemImage::create("f1.png", "f2.png", CC_CALLBACK_1(FilterSample::onNext, this));
	MenuItemImage * pCloseItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(FilterSample::onClose, this));
	MenuItemFont * pClearItem = MenuItemFont::create("Clear Filter", CC_CALLBACK_1(FilterSample::onClearFilter, this));

	pCloseItem->setPosition(VisibleRect::rightBottom(-20, 20));

	Menu * pMenu = Menu::create(item1, item2, item3, pClearItem, pCloseItem, nullptr);
	pMenu->setPosition(Vec2(0, 0));
	Size item2Size = item2->getContentSize();
	item1->setPosition(VisibleRect::bottom(-item2Size.width * 2, item2Size.height / 2));
	item2->setPosition(VisibleRect::bottom(0, item2Size.height / 2));
	item3->setPosition(VisibleRect::bottom(item2Size.width * 2, item2Size.height / 2));
	pClearItem->setPosition(VisibleRect::bottom(0, 100));
	pCloseItem->setPosition(VisibleRect::rightBottom(-item2Size.width / 2, item2Size.height / 2));

	this->addChild(pMenu, 1);

	_nameLabel = Label::createWithSystemFont("Filter Name", "Arial", 28);
	_nameLabel->setPosition(VisibleRect::top(0, -50));
}

void FilterSample::onClose(Ref* pSender) {}

void FilterSample::onRestart(Ref* pSender) {}

void FilterSample::onNext(Ref* pSender) {}

void FilterSample::onBack(Ref* pSender) {}

void FilterSample::onClearFilter(Ref* pSender) {}

Sprite* FilterSample::getFilteredSprite(int index) {}

void FilterSample::update(float delta) {}

void FilterSample::initFilters() {}

void FilterSample::showFilteredDisplay(int index) {}

Sprite* FilterSample::testFilter(Filter* filter, ccLocation location, int order, const char* path) {}

Sprite* FilterSample::testFilter(Filters filters, ccLocation location, int order, const char* path) {}

Sprite* FilterSample::testFilterFromFrame(Filter* filter, ccLocation location, int order, const char* path) {}

Sprite* FilterSample::testFIlterFromFrame(Filters filters, ccLocation location, int order, const char* path) {}

Vec2 FilterSample::getLocation(ccLocation location) {}

GLProgram* FilterSample::getEmboss() {}

cocos2d::GLProgram* FilterSample::getEmbossMov() {}

cocos2d::GLProgram* FilterSample::getColorRamp() {}

cocos2d::GLProgram* FilterSample::getGrass() {}