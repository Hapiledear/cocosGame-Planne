#include"BullteLayer.h"
#include"PlaneLayer.h"

BulletLayer::BulletLayer(void){
	bulletBatchNode = NULL;
	m_pAllBullet = CCArray::create();
	m_pAllBullet->retain();
}
BulletLayer::~BulletLayer(void){
	m_pAllBullet->release();
	m_pAllBullet = NULL;
}
bool BulletLayer::init(){
	bool ret = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("res/assets/ui/shoot.plist", "res/assets/ui/shoot.png");
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->textureForKey("res/assets/ui/shoot.png");
		bulletBatchNode = CCSpriteBatchNode::createWithTexture(texture);//bulletBatchNode为CCSpriteBatchNode类型成员变量  
		this->addChild(bulletBatchNode);

		ret = true;

	} while (0);
	return ret;
}
void BulletLayer::AddBullet(float dt){
	CCSprite* bullet = CCSprite::createWithSpriteFrameName(("bullet1.png"));
	bulletBatchNode->addChild(bullet);//这里子弹要添加到bulletBatchNode中
	this->m_pAllBullet->addObject(bullet);
	//计算起始坐标
	CCPoint planePosition = PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getPosition();
	CCPoint bulletPosition = ccp(planePosition.x, planePosition.y + PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getContentSize().height / 2);
	bullet->setPosition(bulletPosition);
	//终点坐标
	float length = CCDirector::sharedDirector()->getWinSize().height + bullet->getContentSize().height / 2 - bulletPosition.y;
	float velocity = 320 / 1;//飞行速度 320pixel/sec
	float realMoveDuration = length / velocity;//飞行时间
	//动画
	CCFiniteTimeAction* actionMove = CCMoveTo::create(realMoveDuration, ccp(bulletPosition.x, CCDirector::sharedDirector()->getWinSize().height + bullet->getContentSize().height / 2));
	CCFiniteTimeAction* actionDone = CCCallFuncN::create(this, callfuncN_selector(BulletLayer::bulletMoveFinished));//调用子弹回收函数

	CCSequence* sequence = CCSequence::create(actionMove, actionDone, NULL);
	bullet->runAction(sequence);
}
void BulletLayer::startShoot(float delay){
	this->schedule(schedule_selector(BulletLayer::AddBullet), 0.20f, kRepeatForever, delay);//全局定时器
}
void BulletLayer::stopShoot(){
	this->unschedule(schedule_selector(BulletLayer::AddBullet));
}
void BulletLayer::bulletMoveFinished(CCNode* pSender)
{
	CCSprite* bullet = (CCSprite*)pSender;
	this->bulletBatchNode->removeChild(bullet, true);
	this->m_pAllBullet->removeObject(bullet);
}
void BulletLayer::removeBullet(CCSprite* bullet){
	if (bullet!=NULL)
	{
		this->m_pAllBullet->removeObject(bullet);
		this->bulletBatchNode->removeChild(bullet, true);
	}
}
