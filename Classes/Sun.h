#ifndef __SUN_SCENE_H__
#define __SUN_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class Sun : public cocos2d::Sprite
{
public:
	static int ATTs[4];
	static int circles[4];
	static float angle;

	void initSun();
    virtual bool init();
	static Sun* createSun();
	void shootIt();
	void runAnimate();
	void removePao();
	void addLevel();
	int getLevel();
	void removeAnimate(Node *node);
    
    CREATE_FUNC(Sun);
	
private:
	Sprite* sprie;
	Sprite* spr;
	int level;
};

#endif // __HELLOWORLD_SCENE_H__
