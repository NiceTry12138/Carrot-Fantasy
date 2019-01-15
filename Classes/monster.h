#ifndef __MONSTER__H__
#define __MONSTER__H__

#include "cocos2d.h"
USING_NS_CC;

class Monster : public Sprite
{
public:
	static int Speeds[6];
	static int Hps[6];
    virtual bool init();
	int getSpeed();
	int getHp();
	void setHp(int newHp);
	void setSpped(int newSpeed);
	int getNum();
    
	static Monster* createMonster();
	void initMonster();
    
    CREATE_FUNC(Monster);

private:
	void removeMyself();
	ProgressTimer* progress;// 定义进度条指针
	int MonsterNum;
	int Hp;
	int speed;
};

#endif // __HELLOWORLD_SCENE_H__
