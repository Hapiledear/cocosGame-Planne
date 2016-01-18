#include "WelcomLayer.h"
#include "GameScene.h"
#include "GameOverLayer.h"
WelcomeLayer::WelcomeLayer()
{
}

WelcomeLayer::~WelcomeLayer()
{
}
/************************************************************************/
/* 安卓返回按键监听                                                      */
/************************************************************************/
void WelcomeLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)  //返回
	{
		Director::getInstance()->end();
	}
}

bool WelcomeLayer::init(){
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		//png加入全局cache中
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("res/assets/ui/shoot_background.plist");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("res/assets/ui/shoot.plist");

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		//加入background
		CCSprite* background = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		this->addChild(background);

		//加入copyright
		CCSprite* copyright = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("shoot_copyright.png"));
		copyright->setAnchorPoint(ccp(0.5, 0));
		copyright->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		this->addChild(copyright);

		//加入loading
		CCSprite* loading = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
		loading->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 40));
		this->addChild(loading);

		//loading动画

		CCAnimation* animation = CCAnimation::create();//动画对象
		animation->setDelayPerUnit(0.2f);//播放时长，s
		//获取图片，先后次序即为播放顺序
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading2.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading3.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading4.png"));

		CCAnimate* animate = CCAnimate::create(animation);//animation要用animate进行播放
		CCRepeat* repeat = CCRepeat::create(animate, 2);//动作对象，循环次数，若要永远重复则用RepeatForever
		CCCallFuncN* repeatdone = CCCallFuncN::create(this, callfuncN_selector(WelcomeLayer::loadingDone));//播放完成后的操作
		CCSequence* sequence = CCSequence::create(repeat, repeatdone, NULL);//顺序动作
		loading->runAction(sequence);//由loading精灵来播放该animate

		getHighestHistorySorce();

		this->setKeypadEnabled(true);//打开按键监听交互

		bRet = true;
	} while (0);

	return bRet;
}
/************************************************************************/
/*loding动画播放完后的操作                                               */
/************************************************************************/
void WelcomeLayer::loadingDone(CCNode* pNode)
{
	CCScene* pScene = GameScene::create();
	CCTransitionMoveInB *animateScene = CCTransitionMoveInB::create(0.5f, pScene);
	CCDirector::sharedDirector()->replaceScene(animateScene);
}

/************************************************************************/
/* 判断是否有该文件          ，没有则创建                                 */
/************************************************************************/
bool WelcomeLayer::isHaveSaveFile()
{
	if (!CCUserDefault::sharedUserDefault()->getBoolForKey("isHaveSaveFileXml"))
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("isHaveSaveFileXml", true);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("HighestScore", 0);
		CCUserDefault::sharedUserDefault()->flush();
		return false;
	}
	else
	{
		return true;
	}
}
void WelcomeLayer::getHighestHistorySorce()
{
	if (isHaveSaveFile())
	{
		GameOverLayer::highestHistoryScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("HighestScore", 0);
	}
}