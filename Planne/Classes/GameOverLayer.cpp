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
	if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)  //����
	{
		Director::getInstance()->end();
	}
}
/************************************************************************/
/* ���ص�creat����                                                       */
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
		//ֹͣ�������֣�����gameover����Ч
		if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		}
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/game_over.mp3");

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		//����gameover_background
		CCSprite* background = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gameover.png"));
		background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		this->addChild(background);

		//����BackMenu
		CCSprite* normalBackToGame = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_finish.png"));//����״̬�µİ�ťͼƬ
		CCSprite* pressedBackToGame = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_finish.png"));//����״̬�µİ�ťͼƬ
		CCMenuItemImage* pBackItem = CCMenuItemImage::create();//����menu��item
		pBackItem->initWithNormalSprite(normalBackToGame, pressedBackToGame, NULL, this, menu_selector(GameOverLayer::menuBackCallback));//����
		pBackItem->setPosition(ccp(winSize.width - normalBackToGame->getContentSize().width / 2 - 10, normalBackToGame->getContentSize().height / 2 + 10));//λ��
		CCMenu *menuBack = CCMenu::create(pBackItem, NULL);//����menu������item
		menuBack->setPosition(Point::ZERO);//λ��
		this->addChild(menuBack);//����layer

		//����score
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

		//������ʷ��߷�
		//CCLabelTTF* tip=CCLabelTTF::create("Congratulations! Your Score is","Monaco",20);
		//tip->setColor(ccc3(143,146,147));
		//tip->setPosition(ccp(finalScore->getPosition().x,finalScore->getPosition().y+finalScore->getContentSize().height+50));
		//this->addChild(tip);
		CCString* strHighestScore = CCString::createWithFormat("%d", highestHistoryScore);
		highestScore = CCLabelBMFont::create(strHighestScore->_string.c_str(), "res/assets/font/font.fnt");
		highestScore->setColor(ccc3(143, 146, 147));
		highestScore->setAnchorPoint(ccp(0, 0.5));//����ê�㣬��Ϊ���ŵȲ����ķ����㡣
		highestScore->setPosition(ccp(140, winSize.height - 30));
		this->addChild(highestScore);
		//�����������߷ָߣ��������߷֣�����ʾ�����Ŷ���
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
/* ���ذ�ť��Ӧ����                                                                     */
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
