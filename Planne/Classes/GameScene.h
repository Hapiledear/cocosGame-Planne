#ifndef _GameScene_H_
#define _GameScene_h_

#include"cocos2d.h"
#include"GameLayer.h"
class GameScene :public cocos2d::Scene{
public:
	GameScene(void);
	~GameScene(void);
	CREATE_FUNC(GameScene);
	virtual bool init();
	GameLayer* _gameLayer;
};

#endif