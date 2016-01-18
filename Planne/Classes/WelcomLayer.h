#pragma once

#include "cocos2d.h"

USING_NS_CC;
class WelcomeLayer :public CCLayer
{
public:
	WelcomeLayer();
	~WelcomeLayer();
	virtual bool init();
	CREATE_FUNC(WelcomeLayer);
	void loadingDone(CCNode* pNode);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	bool isHaveSaveFile();
	void getHighestHistorySorce();
private:

};

