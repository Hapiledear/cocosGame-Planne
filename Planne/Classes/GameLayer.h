#ifndef _GameLayer_H_
#define _GameLayer_h_
#include"cocos2d.h"

#include "SimpleAudioEngine.h"
#include"PlaneLayer.h"
#include"BullteLayer.h"
#include"EnemyLayer.h"
#include "MutiBulletsLayer.h"
#include "UFOLayer.h"
#include "ControlLayer.h"

USING_NS_CC;

const int ENEMY1_SCORE = 1000;
const int ENEMY2_SCORE = 6000;
const int ENEMY3_SCORE = 30000;

const int MAX_BIGBOOM_COUNT = 100000;
const int TAG_BIGBOOM_MENUITEM = 1;
const int TAG_BIGBOOMCOUNT_LABEL = 2;

class GameLayer :public CCLayer{
public:
	GameLayer(void);
	~GameLayer(void);
	CREATE_FUNC(GameLayer);
	virtual bool init();
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	void update(float delta);

	void backgroundMove(float dt);

	void updateBigBoomItem(int bigBoomCount);
	void menuBigBoomCallback(CCObject* pSender);
	static Level getCurLevel();
private:
	CCSprite* background1;
	CCSprite* background2;

	CCMenu* menuBigBoom;
	CCLabelBMFont* bigBoomCountItem;

	PlaneLayer* planeLayer;
	BulletLayer* bulletLayer;
	EnemyLayer* enemyLayer;
	MutiBulletsLayer* mutiBulletsLayer;
	UFOLayer* ufoLayer;
	ControlLayer* controlLayer;

	int score;
	int bigBoomCount;
	static Level level;
};
#endif