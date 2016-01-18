#include "NoTouchLayer.h"

NoTouchLayer::NoTouchLayer()
{
	auto touchListener = EventListenerTouchOneByOne::create(); //获取单点chuk
	touchListener->onTouchBegan = CC_CALLBACK_2(NoTouchLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(NoTouchLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(NoTouchLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithFixedPriority(touchListener, 2);
}

NoTouchLayer::~NoTouchLayer()
{
}
bool NoTouchLayer::init(){
	if (!CCLayer::init())
	{
		return false;
	}
	setTouchEnabled(true);
	return true;
}


bool NoTouchLayer::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void NoTouchLayer::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void NoTouchLayer::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}