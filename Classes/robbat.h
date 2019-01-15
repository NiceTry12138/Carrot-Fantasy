#ifndef __ROBBAT_SCENE_H__
#define __ROBBAT_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class Robbat : public cocos2d::Sprite
{
public:

    virtual bool init();
    
	static Robbat* createRobbat();

	void initRobbat();

	void runAnimate();

	void HpDown();

	int GetHp();
    
    CREATE_FUNC(Robbat);
private:
	int Hp;
};

#endif // __HELLOWORLD_SCENE_H__
