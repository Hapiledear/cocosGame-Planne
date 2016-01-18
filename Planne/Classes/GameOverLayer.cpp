#include "GameOverLayer.h"
#include "GameScene.h"

int GameOverLayer::highestHistoryScore = 0;

GameOverLayer::GameOverLayer(void)
{
	score = 0;
	highestScore = NULL;
}

GameOverLayer::~GameOverLayer(void)
{
}
void GameOverLayer::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event){
	if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)  //返回
	{
		Director::getInstance()->end();
	}
}
/************************************************************************/
/* 重载的creat函数                                                       */
/************************************************************************/
GameOverLayer* GameOverLayer::create(int passScore)
{
	GameOverLayer *pRet = new GameOverLayer();
	pRet->score = passScore;
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool GameOverLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		//停止背景音乐，播放gameover的音效
		if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		}
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/game_over.mp3");

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		//加载gameover_background
		CCSprite* background = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gameover.png"));
		background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		this->addChild(background);

		//加载BackMenu
		CCSprite* normalBackToGame = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_finish.png"));//正常状态下的按钮图片
		CCSprite* pressedBackToGame = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_finish.png"));//按下状态下的按钮图片
		CCMenuItemImage* pBackItem = CCMenuItemImage::create();//创建menu的item
		pBackItem->initWithNormalSprite(normalBackToGame, pressedBackToGame, NULL, this, menu_selector(GameOverLayer::menuBackCallback));//设置
		pBackItem->setPosition(ccp(winSize.width - normalBackToGame->getContentSize().width / 2 - 10, normalBackToGame->getContentSize().height / 2 + 10));//位置
		CCMenu *menuBack = CCMenu::create(pBackItem, NULL);//创建menu并加入item
		menuBack->setPosition(Point::ZERO);//位置
		this->addChild(menuBack);//加入layer

		//加载score
		CCString* strScore = CCString::createWithFormat("%d", score);
		CCLabelBMFont* finalScore = CCLabelBMFont::create(strScore->_string.c_str(), "res/assets/font/font.fnt");
		finalScore->setColor(ccc3(143, 146, 147));
		finalScore->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		this->addChild(finalScore);

		CCDelayTime* delay = CCDelayTime::create(1.0f);
		CCScaleTo* scalebig = CCScaleTo::create(1.0f, 3.0f);
		CCScaleTo* scalelittle = CCScaleTo::create(0.3f, 2.0f);
		CCCallFunc* showAD = CCCallFunc::create(this, callfunc_selector(GameOverLayer::showAD));
		CCFiniteTimeAction* sequence = CCSequence::create(delay, scalebig, scalelittle, showAD, NULL);
		finalScore->runAction(sequence);

		//加载历史最高分
		//CCLabelTTF* tip=CCLabelTTF::create("Congratulations! Your Score is","Monaco",20);
		//tip->setColor(ccc3(143,146,147));
		//tip->setPosition(ccp(finalScore->getPosition().x,finalScore->getPosition().y+finalScore->getContentSize().height+50));
		//this->addChild(tip);
		CCString* strHighestScore = CCString::createWithFormat("%d", highestHistoryScore);
		highestScore = CCLabelBMFont::create(strHighestScore->_string.c_str(), "res/assets/font/font.fnt");
		highestScore->setColor(ccc3(143, 146, 147));
		highestScore->setAnchorPoint(ccp(0, 0.5));//设置锚点，即为缩放等操作的发生点。
		highestScore->setPosition(ccp(140, winSize.height - 30));
		this->addChild(highestScore);
		//如果分数比最高分高，则更新最高分，并显示，播放动画
		if (score > highestHistoryScore)
		{
			CCUserDefault::sharedUserDefault()->setIntegerForKey("HighestScore", score);
			highestHistoryScore = score;
			CCDelayTime* delayChange = CCDelayTime::create(1.3f);
			CCMoveBy* moveOut = CCMoveBy::create(0.1f, ccp(0, 100));
			CCCallFuncN* beginChange = CCCallFuncN::create(this, callfuncN_selector(GameOverLayer::beginChangeHighestScore));
			CCMoveBy* moveIn = CCMoveBy::create(0.1f, ccp(0, -100));
			CCFiniteTimeAction* sequence = CCSequence::create(delayChange, moveOut, beginChange, moveIn, NULL);
			highestScore->runAction(sequence);
		}

		this->setKeypadEnabled(true);

		bRet = true;
	} while (0);
	return bRet;
}
/************************************************************************/
/* 返回按钮响应函数                                                                     */
/************************************************************************/
void GameOverLayer::menuBackCallback(CCObject* pSender)
{
	CCScene* pScene = GameScene::create();
	CCTransitionSlideInL* animateScene = CCTransitionSlideInL::create(1.0f, pScene);
	CCDirector::sharedDirector()->replaceScene(animateScene);
}



void GameOverLayer::beginChangeHighestScore(CCNode* pNode)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/achievement.mp3");
	CCString* changeScore = CCString::createWithFormat("%d", score);
	highestScore->setString(changeScore->_string.c_str());
}

void GameOverLayer::showAD()
{

}
