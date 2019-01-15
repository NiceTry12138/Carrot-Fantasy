#include "Setting.h"
#include "SimpleAudioEngine.h"
#include "MainGame2.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* Setting::createScene()
{
    return Setting::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Setting::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto bakGround = Sprite::createWithSpriteFrameName("BackGround3.png");
	this->addChild(bakGround);
	bakGround->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

	// 背景音乐开关按钮
	auto closeMusic = MenuItemImage::create("SettingStar/MusicClose.png","SettingStar/MusicClose.png");
	auto openMusic = MenuItemImage::create("SettingStar/MusicOpen.png","SettingStar/MusicOpen.png");
	itemImage = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::open_Music, this), closeMusic, openMusic ,NULL);
	itemImage->setPosition(Point(itemImage->getPositionX(), itemImage->getPositionY()));

	// 回到主页面

	auto returnMain = MenuItemImage::create("SettingStar/home1.png", "SettingStar/home2.png", CC_CALLBACK_0(Setting::Return_HOME, this));
	returnMain->setPosition(Point(visibleSize.width/2 - returnMain->getContentSize().width/2 , visibleSize.height/2 - returnMain->getContentSize().height/2));
	
	// 关于我
	auto aboutMe = MenuItemImage::create("SettingStar/AboutMe1.png", "SettingStar/AboutMe2.png", CC_CALLBACK_0(Setting::openURL, this));
	aboutMe->setPosition(Point(aboutMe->getPositionX(), aboutMe->getPositionY()+310));
	// 同步数据
	auto sendData = MenuItemImage::create("SettingStar/tongbu1.png", "SettingStar/tongbu2.png", CC_CALLBACK_0(Setting::Send_Data, this));
	sendData->setPosition(Point(sendData->getPositionX(), sendData->getPositionY() - 120));

	auto menu = Menu::create(itemImage, aboutMe, sendData, returnMain, NULL);

	this->addChild(menu);


    return true;
}


void Setting::open_Music(cocos2d::Ref * pSender)
{
	CCLOG("stop music in setting");
	auto item1 = (MenuItemToggle*)pSender;
	if (item1->getSelectedIndex() == 0) {
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else
	{
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}


void Setting::openURL()
{
	Application::getInstance()->openURL("https://dyryamo.github.io/");
}

void Setting::Send_Data()
{
	Internet::getInstance()->sendNewUser(Internet::getInstance()->getTheUserName(), MainGame2::grade);
}

void Setting::Return_HOME()
{
	Director::getInstance()->popScene();
}

void Setting::onEnter()
{
	Scene::onEnter();
	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
		itemImage->setSelectedIndex(1);
	}
	else {
		itemImage->setSelectedIndex(0);
	}
}



