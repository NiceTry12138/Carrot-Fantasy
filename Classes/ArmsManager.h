#ifndef __ARMSMANAGE_SCENE_H__
#define __ARMSMANAGE_SCENE_H__

#include "cocos2d.h"
#include "monster.h"
#include "robbat.h"
#include "arms.h"
#include "Sun.h"
#include "Setting.h"

using namespace cocos2d;

class ArmsManage
{
public:
	static ArmsManage* getInstance();
	void addPao(Arms* pao);
	void addSun(Sun* sun);
	void addMonster(Monster* monster);

	void erasePao(Arms* pao);
	void eraseSun(Sun* sun);
	void eraseMonster(Monster* monster);

	Vector<Arms *>* getPaos();
	Vector<Sun *>* getSuns();
	Vector<Monster *>* getMonster();


private:
	static ArmsManage* armsManage;
	Vector<Arms *> Paos;
	Vector<Sun *> Suns;
	Vector<Monster *> Monsters;
};

#endif // __HELLOWORLD_SCENE_H__
