#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Internet.h"
#include "HelloWorldScene.h"
using namespace cocos2d;

class Setting : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void open_Music(cocos2d::Ref* pSender);
	void openURL();
	void Send_Data();
	void Return_HOME();
	virtual void onEnter();
	MenuItemToggle* itemImage;
    CREATE_FUNC(Setting);
};

#endif // __HELLOWORLD_SCENE_H__
