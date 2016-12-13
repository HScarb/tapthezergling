#include "Circle.h"
USING_NS_CC;

Circle* Circle::createByColor(int color)
{
	auto cir = new Circle();

	if (cir && cir->init(color))
	{
		cir->autorelease();
		return cir;
	}
	else
	{
		CC_SAFE_DELETE(cir);
		return nullptr;
	}
}