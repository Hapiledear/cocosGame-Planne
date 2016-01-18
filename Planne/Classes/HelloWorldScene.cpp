#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include"GameScene.h"
USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("WelcomeScene.csb");
	
    addChild(rootNode);
	Button* PlayGame_btn = dynamic_cast<Button*>(rootNode->getChildByName("Button_1"));
	//Ìí¼Ó¼àÌý
	PlayGame_btn->addClickEventListener(CC_CALLBACK_1(HelloWorld::PlayGame_btn_Callback, this));

    return true;
}
void HelloWorld::PlayGame_btn_Callback(cocos2d::Ref* pSender){
	CCLOG("go to game");
	Director::getInstance()->replaceScene(GameScene::create());
}