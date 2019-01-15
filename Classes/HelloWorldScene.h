#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "monster.h"
#include "robbat.h"
#include "arms.h"
#include "Sun.h"
#include "Setting.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_EXT;
using namespace cocos2d;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void menuCloseCallback(cocos2d::Ref* pSender);
	void open_Music(cocos2d::Ref* pSender);
	void ToSetting();
	float getAngle(float OriX, float OriY, float FinX, float FinY);
	void toMainGame1();
	void quitGame();
	EditBox* editBoxUserName;
	virtual void onEnter();
	MenuItemToggle* toggle1;
    CREATE_FUNC(HelloWorld);

};

#endif // __HELLOWORLD_SCENE_H__
