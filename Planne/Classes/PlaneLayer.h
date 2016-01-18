#include"cocos2d.h"

USING_NS_CC;
const int AIRPLANE = 747;

class PlaneLayer : public CCLayer{
public:
	PlaneLayer(void);
	~PlaneLayer(void);
	virtual bool init();
	static PlaneLayer* create();
	void MoveTo(CCPoint location);
	void BlowUp(int passScore);
	void RemovePlane();
public:
	static PlaneLayer* sharedPlane;
	bool isAlive;
	int score;


};