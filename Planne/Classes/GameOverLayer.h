#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class GameOverLayer :
	public CCLayer
{
public:
	GameOverLayer(void);

	~GameOverLayer(void);

	virtual bool init();

	static GameOverLayer* create(int passScore);

	void menuBackCallback(CCObject* pSender);

	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

	void beginChangeHighestScore(CCNode* pNode);

	void showAD();

public:

	int score;

	static int highestHistoryScore;

	CCLabelBMFont* highestScore;
};