#ifndef __MainGame2_H__
#define __MainGame2_H__

#include "cocos2d.h"
#include "monster.h"
#include "Internet.h"
#include "robbat.h"
#include "arms.h"
#include "Sun.h"
#include "Setting.h"
#include "HelloWorldScene.h"
#include "ArmsManager.h"

using namespace cocos2d;

class MainGame2 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	Robbat* robbat;
	Vector<Monster*> monsters;

	void createMonster(float dt);

	void RobbatHpDown(Node* node);
	void starCreateMonster(float dt);
	void toSettingScene();
	void toHomeScene();
	void jiaSu(cocos2d::Ref * pSender);
	void createSun();
	void createPao();
	void createUp();
	void createCloas();

	bool MenuCreateOrNot;
	float Monsterspeed;
	float creataMonsterTime;

	bool onTouchBegaan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

	void Myupdate(float delta);
	float getR(Point a, Point b);
	float changeAngle(Point a, Point b);
	bool inMapLoad(Point point);

	Point TouchPoint;

	MenuItemImage* pao;
	MenuItemImage* sun;
	Menu* PaoAndSun;

	TMXTiledMap* tilemap;

	MenuItemImage* upIt;
	MenuItemImage* closeIt;
	Menu* MenuIt;

	Arms* selectArms;
	Sun* selectSun;
	Point started, finished;
	int MonsterNum;
	static int grade;

    
    CREATE_FUNC(MainGame2);
};

#endif // __HELLOWORLD_SCENE_H__
