#include"cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
class BulletLayer :public CCLayer{
public:
	BulletLayer(void);
	~BulletLayer(void);
	CREATE_FUNC(BulletLayer);
	virtual bool init();
	void AddBullet(float dt);
	void startShoot(float delay=0.0f);
	void stopShoot();
	void bulletMoveFinished(CCNode* pSender);
	void removeBullet(CCSprite* bullet);
public:
	CCSpriteBatchNode* bulletBatchNode;
	CCArray* m_pAllBullet;
};