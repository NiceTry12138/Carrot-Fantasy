#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "monster.h"
#include "robbat.h"
#include "arms.h"
#include "Sun.h"
#include "Setting.h"
#include "extensions/cocos-ext.h"
#include "MainGame2.h"
#include "HelloWorldScene.h"

USING_NS_CC_EXT;
using namespace cocos2d;

class GameOver : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void ExitGame();
	void ResumGame();
	void ToHome();
	
    CREATE_FUNC(GameOver);

};

#endif // __HELLOWORLD_SCENE_H__
