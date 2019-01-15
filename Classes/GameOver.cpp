#pragma execution_character_set("utf-8")
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MainGame1.h"
#include "GameOver.h"

#define PI 3.14159265359

using namespace CocosDenshion;
USING_NS_CC;
using namespace std;


Scene* GameOver::createScene()
{
    return GameOver::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameOver::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto BGPIC = Sprite::create("SettingStar/GameOver.png");
	this->addChild(BGPIC);
	BGPIC->setPosition(Point(visibleSize.width/2, visibleSize.height/2));

	auto item1 = MenuItemImage::create("SettingStar/onPlay.png", "SettingStar/onPlayed.png", CC_CALLBACK_0(GameOver::ResumGame, this));
	auto quitItem = MenuItemImage::create("SettingStar/quit.png", "SettingStar/quit1.png", CC_CALLBACK_0(GameOver::ExitGame, this));
	auto returnMain = MenuItemImage::create("SettingStar/home1.png", "SettingStar/home2.png", CC_CALLBACK_0(GameOver::ToHome, this));

	item1->setPosition(Point(-item1->getContentSize().width, -item1->getContentSize().height));
	quitItem->setPosition(Point(quitItem->getContentSize().width, -item1->getContentSize().height));
	returnMain->setPosition(Point(0, -item1->getContentSize().height));

	auto menu = Menu::create(item1, quitItem, returnMain, NULL);
	this->addChild(menu);

		
    return true;
}

void GameOver::ExitGame()
{
	Director::getInstance()->end();
}

void GameOver::ResumGame()
{
	Director::getInstance()->replaceScene(MainGame2::createScene());
}

void GameOver::ToHome()
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}
