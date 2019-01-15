#ifndef __MAINGAME1_SCENE_H__
#define __MAINGAME1_SCENE_H__

#include "cocos2d.h"
#include "Internet.h"
#include "MainGame2.h"
using namespace cocos2d;

class MainGame1 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(MainGame1);

	void changeToMainGame();

	void timeCount(float f);

	void removeCountTime();
	void startSchedule(float f);

	int time;
	Label* welCome;
	Label* playStar;
	Label* countTIme;
	Label* BestGrade;
};

#endif // __HELLOWORLD_SCENE_H__
