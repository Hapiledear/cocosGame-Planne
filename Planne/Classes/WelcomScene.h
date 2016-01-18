#pragma  once

#include "cocos2d.h"
#include "WelcomLayer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
class WelcomScene :public CCScene
{
public:
	WelcomScene();
	~WelcomScene();
	virtual bool init();
	CREATE_FUNC(WelcomScene);

	void PreloadMusic();

private:
	WelcomeLayer* _welcomeLayer;
};

