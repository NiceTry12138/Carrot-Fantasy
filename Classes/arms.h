#ifndef __ARM_SCENE_H__
#define __ARM_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class Arms : public cocos2d::Sprite
{
public:

	static int ATTs[4];//¹¥»÷Á¦
    virtual bool init();

	static Arms* createArms(int num);

	void initArm(int num);

	void runRotate(int angle);
	void shootIt(Point point);
	void addLevel();
	int getLevel();
	void removePao();
	void stopShoot();
    
    CREATE_FUNC(Arms);

private:
	Sprite* sprie;
	bool shoot;
	int level;
	int num;
};

#endif // __HELLOWORLD_SCENE_H__
