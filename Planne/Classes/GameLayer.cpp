#include"GameLayer.h"


Level GameLayer::level = EASY;
GameLayer::GameLayer(void){
	//触摸事件的注册与捕捉
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	background1 = NULL;
	background2 = NULL;
	planeLayer = NULL;
	bulletLayer = NULL;
	mutiBulletsLayer = NULL;
	controlLayer = NULL;
	enemyLayer = NULL;
	ufoLayer = NULL;

	score = 0;
	bigBoomCount = 0;
}
GameLayer::~GameLayer(void){

}
//安卓返回键
void GameLayer::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event){
	if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)  //返回
	{
		Director::getInstance()->end();
	}
}
bool GameLayer::init(){
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		//初始化level
		level = EASY;
		//加载background Music
		if (!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.mp3", true);
		}
		//加载background1
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("res/assets/ui/shoot_background.plist");

		background1 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		
		background1->setAnchorPoint(ccp(0, 0));
		background1->setPosition(ccp(0, 0));
		this->addChild(background1);
		//加载background2
		background2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background2->setAnchorPoint(ccp(0, 0));
		background2->setPosition(ccp(0, background2->getContentSize().height - 2));
		this->addChild(background2);
		//加入planeLayer
		this->planeLayer = PlaneLayer::create();
		this->addChild(planeLayer);
		//加入bulletLayer
		this->bulletLayer = BulletLayer::create();
		this->addChild(bulletLayer);
		this->bulletLayer->startShoot();
		//加入mutiBulletsLayer
		this->mutiBulletsLayer = MutiBulletsLayer::create();
		this->addChild(mutiBulletsLayer);
		//加入enemyLayer
		this->enemyLayer = EnemyLayer::create();
		this->addChild(enemyLayer);

		//加入controlLayer
		this->controlLayer = ControlLayer::create();
		this->addChild(controlLayer);
		//加入UFOLayer
		this->ufoLayer = UFOLayer::create();
		this->addChild(ufoLayer);
		//设置可触摸
		this->setTouchEnabled(true);

		//执行任务计划（背景移动）
		this->schedule(schedule_selector(GameLayer::backgroundMove), 0.01f);

		//碰撞检测
		this->scheduleUpdate();

		//设置按键有效
		this->setKeypadEnabled(true);

		bRet = true;
	} while (0);
	return bRet;
}
/************************************************************************/
/* 移动飞机，实际上是移动背景                                                                     */
/************************************************************************/
void GameLayer::backgroundMove(float dt){
	background1->setPositionY(background1->getPositionY() - 2);
	background2->setPositionY(background1->getPositionY() + background1->getContentSize().height - 2);
	if (background2->getPositionY() == 0)
	{
		background1->setPositionY(0);
	}
}
/************************************************************************/
/* 消耗touch事件                                                 */
/************************************************************************/
bool GameLayer::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	return true;
}
/************************************************************************/
/* 飞机跟随触摸的移动                                                                     */
/************************************************************************/
void GameLayer::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
	if (this->planeLayer->isAlive)//飞机还活着
	{
		CCPoint beginPoint = pTouch->getLocationInView();
		beginPoint = CCDirector::sharedDirector()->convertToGL(beginPoint); //获取触摸坐标  
		//juggle the area of drag   
		CCRect planeRect = this->planeLayer->getChildByTag(AIRPLANE)->boundingBox();//获取飞机当前位置形状位置  
		planeRect.origin.x -= 15;
		planeRect.origin.y -= 15;
		planeRect.size.width += 30;
		planeRect.size.height += 30;//允许稍微加大一点触摸位置，游戏实际需要  
		
		if (planeRect.containsPoint(this->getParent()->convertTouchToNodeSpace(pTouch)) == true) //判断触摸点是否在飞机范围内  
		{
			CCPoint endPoint = pTouch->getPreviousLocationInView();//获取触摸的前一个位置  
			endPoint = CCDirector::sharedDirector()->convertToGL(endPoint);

			CCPoint offSet = ccpSub(beginPoint, endPoint);//获取offset，两点之差，既位移量
			CCPoint toPoint = ccpAdd(this->planeLayer->getChildByTag(AIRPLANE)->getPosition(), offSet); //获取真正移动位置  
			this->planeLayer->MoveTo(toPoint); //移动飞机  
		}
	}
}

void GameLayer::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent){

}

void GameLayer::update(float delta){
	//难度改变
	if (level == EASY && score >= 1000000)
	{
		level = MIDDLE;
	}
	else if (level == MIDDLE && score >= 2000000)
	{
		level = HARD;
	}


	//单子弹层对敌机的碰撞检测
	CCArray* bulletsToDelete = CCArray::create();//创建一个CCArray，用以存放待删除的子弹，也就是此帧中被检测到碰撞的子弹 
	bulletsToDelete->retain();//必须调用retain，CCArray内部调用了autoRelease
	CCObject* bt, *et,*ut;
	//一号敌机的判断
	CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet, bt)//遍历子弹
	{
		CCSprite* bullet = (CCSprite*)bt;

		CCArray* enemy1sToDelete = CCArray::create();
		enemy1sToDelete->retain();
		int a = this->enemyLayer->m_pAllEnemy1->capacity();//获取数组大小
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1, et)//遍历敌机
		{
			Enemy* enemy1 = (Enemy*)et;
			if (bullet->boundingBox().intersectsRect(enemy1->getBoundingBox()))
			{
				if (enemy1->getLife() == 1)
				{
					enemy1->loseLife();
					bulletsToDelete->addObject(bullet);
					enemy1sToDelete->addObject(enemy1);
					score += ENEMY1_SCORE;
					this->controlLayer->updateScore(score);
				}
				else;
			}
		}
		CCARRAY_FOREACH(enemy1sToDelete, et)//消除敌机
		{
			Enemy* enemy1 = (Enemy*)et;
			this->enemyLayer->Enemy1BlowUp(enemy1);
		}
		enemy1sToDelete->release();
	}
	CCARRAY_FOREACH(bulletsToDelete, bt)//消除子弹
	{
		CCSprite* bullet = (CCSprite*)bt;
		this->bulletLayer->removeBullet(bullet);
	}
	bulletsToDelete->removeAllObjects();

	//二号敌机的判断
	CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet, bt)
	{
		CCSprite* bullet = (CCSprite*)bt;

		CCArray* enemy2sToDelete = CCArray::create();
		enemy2sToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy2, et)
		{
			Enemy* enemy2 = (Enemy*)et;
			if (bullet->boundingBox().intersectsRect(enemy2->getBoundingBox()))
			{
				if (enemy2->getLife() > 1)
				{
					enemy2->loseLife();
					bulletsToDelete->addObject(bullet);
				}
				else if (enemy2->getLife() == 1)
				{
					enemy2->loseLife();
					bulletsToDelete->addObject(bullet);
					enemy2sToDelete->addObject(enemy2);
					score += ENEMY2_SCORE;
					this->controlLayer->updateScore(score);
				}
				else;
			}
		}
		CCARRAY_FOREACH(enemy2sToDelete, et)
		{
			Enemy* enemy2 = (Enemy*)et;
			this->enemyLayer->Enemy2BlowUp(enemy2);
		}
		enemy2sToDelete->release();
	}
	CCARRAY_FOREACH(bulletsToDelete, bt)
	{
		CCSprite* bullet = (CCSprite*)bt;
		this->bulletLayer->removeBullet(bullet);
	}
	bulletsToDelete->removeAllObjects();
	
	//三号敌机的判断
	CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet, bt)//遍历所有子弹
	{
		CCLOG("bullets子弹遍历完毕");
		CCSprite* bullet = (CCSprite*)bt;

		CCArray* enemy3sToDelete = CCArray::create();//创建一个CCArray，用以存放待删除的敌机，也就是此子弹击中的敌机
		enemy3sToDelete->retain();//调用retain  
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy3, et)//遍历所有敌机
		{
			CCLOG("enemys敌机便利完毕");
			Enemy* enemy3 = (Enemy*)et;
			if (bullet->boundingBox().intersectsRect(enemy3->getBoundingBox()))//检测碰撞，即矩形区域是否相交  
			{ 
				CCLOG("crash开始检测碰撞");
				//如果life>1,移除bullet
				if (enemy3->getLife() > 1)//因为Enemy3设置了生命值为5  
				{
					enemy3->loseLife();
					bulletsToDelete->addObject(bullet);//把待删除子弹放入CCArray
				}
				//如果life==1,移除enemy3
				else if (enemy3->getLife() == 1)//只剩一条命的时候，再碰撞就挂掉了
				{
					enemy3->loseLife();
					bulletsToDelete->addObject(bullet);//把待删除子弹放入CCArray  
					enemy3sToDelete->addObject(enemy3);//把待删除敌机放入CCArray 
					score += ENEMY3_SCORE;
					this->controlLayer->updateScore(score);
				}
				//此时处在敌机爆炸动画阶段,敌机未消失，子弹还有打到的机会，所以不进行检测
				else;
			}
		}
		CCARRAY_FOREACH(enemy3sToDelete, et)//遍历所有此帧中碰撞死亡的敌机，必须是死亡
		{
			Enemy* enemy3 = (Enemy*)et;
			this->enemyLayer->Enemy3BlowUp(enemy3);//执行爆炸
		}
		enemy3sToDelete->release();//release
	}
	CCARRAY_FOREACH(bulletsToDelete, bt)//遍历所有此帧中碰撞的子弹
	{
		CCSprite* bullet = (CCSprite*)bt;
		this->bulletLayer->removeBullet(bullet);//执行移除
	}
	bulletsToDelete->removeAllObjects();
	bulletsToDelete->release();//release
	
	//多子弹层对敌机的碰撞检测
	CCArray* mutiBulletsToDelete = CCArray::create();
	mutiBulletsToDelete->retain();
	CCObject* mbt;
	////enemy1 & mutiBullets CheckCollosion
	CCARRAY_FOREACH(this->mutiBulletsLayer->m_pAllMutiBullets, mbt)
	{
		CCSprite* mutiBullets = (CCSprite*)mbt;
		CCArray* enemy1sToDelete = CCArray::create();
		enemy1sToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1, et)
		{
			Enemy* enemy1 = (Enemy*)et;
			if (mutiBullets->boundingBox().intersectsRect(enemy1->getBoundingBox()))
			{
				if (enemy1->getLife() == 1)
				{
					enemy1->loseLife();
					mutiBulletsToDelete->addObject(mutiBullets);
					enemy1sToDelete->addObject(enemy1);
					score += ENEMY1_SCORE;
					this->controlLayer->updateScore(score);
				}
				else;
			}
		}
		CCARRAY_FOREACH(enemy1sToDelete, et)
		{
			Enemy* enemy1 = (Enemy*)et;
			this->enemyLayer->Enemy1BlowUp(enemy1);
		}
		enemy1sToDelete->release();
	}
	CCARRAY_FOREACH(mutiBulletsToDelete, mbt)
	{
		CCSprite* mutiBullets = (CCSprite*)mbt;
		this->mutiBulletsLayer->RemoveMutiBullets(mutiBullets);
	}
	mutiBulletsToDelete->removeAllObjects();

	//enemy2 & mutiBullets CheckCollosion
	CCARRAY_FOREACH(this->mutiBulletsLayer->m_pAllMutiBullets, mbt)
	{
		CCSprite* mutiBullets = (CCSprite*)mbt;

		CCArray* enemy2sToDelete = CCArray::create();
		enemy2sToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy2, et)
		{
			Enemy* enemy2 = (Enemy*)et;
			if (mutiBullets->boundingBox().intersectsRect(enemy2->getBoundingBox()))
			{
				if (enemy2->getLife() > 1)
				{
					enemy2->loseLife();
					mutiBulletsToDelete->addObject(mutiBullets);
				}
				else if (enemy2->getLife() == 1)
				{
					enemy2->loseLife();
					mutiBulletsToDelete->addObject(mutiBullets);
					enemy2sToDelete->addObject(enemy2);
					score += ENEMY2_SCORE;
					this->controlLayer->updateScore(score);
				}
				else;
			}
		}
		CCARRAY_FOREACH(enemy2sToDelete, et)
		{
			Enemy* enemy2 = (Enemy*)et;
			this->enemyLayer->Enemy2BlowUp(enemy2);
		}
		enemy2sToDelete->release();
	}
	CCARRAY_FOREACH(mutiBulletsToDelete, mbt)
	{
		CCSprite* mutiBullets = (CCSprite*)mbt;
		this->mutiBulletsLayer->RemoveMutiBullets(mutiBullets);
	}
	mutiBulletsToDelete->removeAllObjects();

	//enemy3 & mutiBullets CheckCollosion
	CCARRAY_FOREACH(this->mutiBulletsLayer->m_pAllMutiBullets, mbt)
	{
		CCSprite* mutiBullets = (CCSprite*)mbt;

		CCArray* enemy3sToDelete = CCArray::create();
		enemy3sToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy3, et)
		{
			Enemy* enemy3 = (Enemy*)et;
			if (mutiBullets->boundingBox().intersectsRect(enemy3->getBoundingBox()))
			{
				//
				if (enemy3->getLife() > 1)
				{
					enemy3->loseLife();
					mutiBulletsToDelete->addObject(mutiBullets);
				}
				//
				else if (enemy3->getLife() == 1)
				{
					enemy3->loseLife();
					mutiBulletsToDelete->addObject(mutiBullets);
					enemy3sToDelete->addObject(enemy3);
					score += ENEMY3_SCORE;
					this->controlLayer->updateScore(score);
				}
				
				else;
			}
		}
		CCARRAY_FOREACH(enemy3sToDelete, et)
		{
			Enemy* enemy3 = (Enemy*)et;
			this->enemyLayer->Enemy3BlowUp(enemy3);
		}
		enemy3sToDelete->release();
	}
	CCARRAY_FOREACH(mutiBulletsToDelete, mbt)
	{
		CCSprite* mutiBullets = (CCSprite*)mbt;
		this->mutiBulletsLayer->RemoveMutiBullets(mutiBullets);
	}
	mutiBulletsToDelete->removeAllObjects();
	mutiBulletsToDelete->release();

	//敌机与主角碰撞
	CCRect airplaneRect = this->planeLayer->getChildByTag(AIRPLANE)->boundingBox();
	airplaneRect.origin.x += 30;
	airplaneRect.size.width -= 60;
	//enemy1 & airplane CheckCollosion
	CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1, et)
	{
		Enemy* enemy1 = (Enemy*)et;
		if (enemy1->getLife() > 0)
		{
			if (airplaneRect.intersectsRect(enemy1->getBoundingBox()))
			{
				
				this->unscheduleAllSelectors();
				this->bulletLayer->stopShoot();
				this->mutiBulletsLayer->StopShoot();
				this->planeLayer->BlowUp(score);
				return;
			}
		}
	}
	//enemy2 & airplane CheckCollosion
	CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy2, et)
	{
		Enemy* enemy2 = (Enemy*)et;
		if (enemy2->getLife() > 0)
		{
			if (airplaneRect.intersectsRect(enemy2->getBoundingBox()))
			{
				//停止所有业务
				this->unscheduleAllSelectors();
				this->bulletLayer->stopShoot();
				this->mutiBulletsLayer->StopShoot();
				this->planeLayer->BlowUp(score);
				return;
			}
		}
	}
	//enemy3 & airplane CheckCollosion
	CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy3, et)
	{
		Enemy* enemy3 = (Enemy*)et;
		if (enemy3->getLife() > 0)
		{
			if (airplaneRect.intersectsRect(enemy3->getBoundingBox()))
			{
				//Ð¶ÔØËùÓÐÈÎÎñ¼Æ»®
				this->unscheduleAllSelectors();
				this->bulletLayer->stopShoot();
				this->mutiBulletsLayer->StopShoot();
				this->planeLayer->BlowUp(score);
				return;
			}
		}
	}
	//道具层对主角的碰撞检测
	//mutiBullets & airplane CheckCollision
	CCARRAY_FOREACH(this->ufoLayer->m_pAllMutiBullets, ut)
	{
		CCSprite* mutiBullets = (CCSprite*)ut;
		if (this->planeLayer->getChildByTag(AIRPLANE)->boundingBox().intersectsRect(mutiBullets->boundingBox()))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/get_double_laser.mp3");
			this->ufoLayer->RemoveMutiBullets(mutiBullets);
			this->bulletLayer->stopShoot();
			this->mutiBulletsLayer->StartShoot();
			this->bulletLayer->startShoot(6.2f);
		}
	}

	//bigBoom & airplane CheckCollision
	CCARRAY_FOREACH(this->ufoLayer->m_pAllBigBoom, ut)
	{
		CCSprite* bigBoom = (CCSprite*)ut;
		if (this->planeLayer->getChildByTag(AIRPLANE)->boundingBox().intersectsRect(bigBoom->boundingBox()))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/get_bomb.mp3");
			this->ufoLayer->RemoveBigBoom(bigBoom);
			bigBoomCount++;
			updateBigBoomItem(bigBoomCount);
		}
	}
}

void GameLayer::updateBigBoomItem(int bigBoomCount)
{
	CCSprite* normalBomb = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bomb.png"));
	CCSprite* pressedBomb = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bomb.png"));
	if (bigBoomCount < 0)
	{
		return;
	}
	else if (bigBoomCount == 0)
	{
		if (this->getChildByTag(TAG_BIGBOOM_MENUITEM))
		{
			this->removeChildByTag(TAG_BIGBOOM_MENUITEM, true);
		}
		if (this->getChildByTag(TAG_BIGBOOMCOUNT_LABEL))
		{
			this->removeChildByTag(TAG_BIGBOOMCOUNT_LABEL, true);
		}
	}
	else if (bigBoomCount == 1)
	{
		//加入bigBoomItemMenu
		if (!this->getChildByTag(TAG_BIGBOOM_MENUITEM))
		{
			CCMenuItemImage* pBigBoomItem = CCMenuItemImage::create();
			pBigBoomItem->initWithNormalSprite(normalBomb, pressedBomb, NULL, this, menu_selector(GameLayer::menuBigBoomCallback));
			pBigBoomItem->setPosition(ccp(normalBomb->getContentSize().width / 2 + 10, normalBomb->getContentSize().height / 2 + 10));
			menuBigBoom = CCMenu::create(pBigBoomItem, NULL);
			menuBigBoom->setPosition(Point::ZERO);
			this->addChild(menuBigBoom, 0, TAG_BIGBOOM_MENUITEM);
		}
		if (this->getChildByTag(TAG_BIGBOOMCOUNT_LABEL))
		{
			this->removeChildByTag(TAG_BIGBOOMCOUNT_LABEL, true);
		}
	}
	else
	{
		if (!this->getChildByTag(TAG_BIGBOOM_MENUITEM))
		{
			CCMenuItemImage* pBigBoomItem = CCMenuItemImage::create();
			pBigBoomItem->initWithNormalSprite(normalBomb, pressedBomb, NULL, this, menu_selector(GameLayer::menuBigBoomCallback));
			pBigBoomItem->setPosition(ccp(normalBomb->getContentSize().width / 2 + 10, normalBomb->getContentSize().height / 2 + 10));
			menuBigBoom = CCMenu::create(pBigBoomItem, NULL);
			menuBigBoom->setPosition(Point::ZERO);
			this->addChild(menuBigBoom, 0, TAG_BIGBOOM_MENUITEM);
		}
		if (this->getChildByTag(TAG_BIGBOOMCOUNT_LABEL))
		{
			this->removeChildByTag(TAG_BIGBOOMCOUNT_LABEL, true);
		}
		if (bigBoomCount >= 0 && bigBoomCount <= MAX_BIGBOOM_COUNT)
		{
			CCString* strScore = CCString::createWithFormat("X%d", bigBoomCount);
			
			bigBoomCountItem = CCLabelBMFont::create(strScore->_string.c_str(), "res/assets/font/font.fnt");
			bigBoomCountItem->setColor(ccc3(143, 146, 147));
			bigBoomCountItem->setAnchorPoint(ccp(0, 0.5));
			bigBoomCountItem->setPosition(ccp(normalBomb->getContentSize().width + 15, normalBomb->getContentSize().height / 2 + 5));
			this->addChild(bigBoomCountItem, 0, TAG_BIGBOOMCOUNT_LABEL);
		}
	}
}
void GameLayer::menuBigBoomCallback(CCObject* pSender)
{
	if (bigBoomCount > 0 && !CCDirector::sharedDirector()->isPaused())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/use_bomb.mp3");
		bigBoomCount--;
		score += this->enemyLayer->m_pAllEnemy1->count()*ENEMY1_SCORE;
		score += this->enemyLayer->m_pAllEnemy2->count()*ENEMY2_SCORE;
		score += this->enemyLayer->m_pAllEnemy3->count()*ENEMY3_SCORE;
		this->enemyLayer->removeAllEnemy();
		updateBigBoomItem(bigBoomCount);
		this->controlLayer->updateScore(score);
	}
}
Level GameLayer::getCurLevel(){
	return level;
}