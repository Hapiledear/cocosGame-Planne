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
		bulletBatchNode = CCSpriteBatchNode::createWithTexture(texture);//bulletBatchNodeΪCCSpriteBatchNode���ͳ�Ա����  
		this->addChild(bulletBatchNode);

		ret = true;

	} while (0);
	return ret;
}
void BulletLayer::AddBullet(float dt){
	CCSprite* bullet = CCSprite::createWithSpriteFrameName(("bullet1.png"));
	bulletBatchNode->addChild(bullet);//�����ӵ�Ҫ��ӵ�bulletBatchNode��
	this->m_pAllBullet->addObject(bullet);
	//������ʼ����
	CCPoint planePosition = PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getPosition();
	CCPoint bulletPosition = ccp(planePosition.x, planePosition.y + PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getContentSize().height / 2);
	bullet->setPosition(bulletPosition);
	//�յ�����
	float length = CCDirector::sharedDirector()->getWinSize().height + bullet->getContentSize().height / 2 - bulletPosition.y;
	float velocity = 320 / 1;//�����ٶ� 320pixel/sec
	float realMoveDuration = length / velocity;//����ʱ��
	//����
	CCFiniteTimeAction* actionMove = CCMoveTo::create(realMoveDuration, ccp(bulletPosition.x, CCDirector::sharedDirector()->getWinSize().height + bullet->getContentSize().height / 2));
	CCFiniteTimeAction* actionDone = CCCallFuncN::create(this, callfuncN_selector(BulletLayer::bulletMoveFinished));//�����ӵ����պ���

	CCSequence* sequence = CCSequence::create(actionMove, actionDone, NULL);
	bullet->runAction(sequence);
}
void BulletLayer::startShoot(float delay){
	this->schedule(schedule_selector(BulletLayer::AddBullet), 0.20f, kRepeatForever, delay);//ȫ�ֶ�ʱ��
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
