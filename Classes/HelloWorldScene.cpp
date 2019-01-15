#pragma execution_character_set("utf-8")
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MainGame1.h"

#define PI 3.14159265359

using namespace CocosDenshion;
USING_NS_CC;
using namespace std;


Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGMusic.mp3");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("BGMusic.mp3", true);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("robbat/RobAnimate.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("arms/2/Sun.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mons_die/monsdie.plist", "mons_die/monsdie.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SettingStar/MainSet.plist", "SettingStar/MainSet.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("load/load.plist", "load/load.png");
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto item1 = MenuItemImage::create("SettingStar/onPlay.png","SettingStar/onPlayed.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	auto quitItem = MenuItemImage::create("SettingStar/quit.png", "SettingStar/quit1.png", CC_CALLBACK_0(HelloWorld::quitGame, this));

	auto music1 = MenuItemImage::create("SettingStar/inMusic1.png", "SettingStar/inMusic1.png");
	auto music2 = MenuItemImage::create("SettingStar/inMusic2.png", "SettingStar/inMusic2.png");
	toggle1 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::open_Music, this), music1, music2, NULL);
	
	auto sett = MenuItemImage::create("SettingStar/setIcon.png", "SettingStar/setIcon2.png", CC_CALLBACK_0(HelloWorld::ToSetting, this));

	sett->setPosition(Point(visibleSize.width / 2 - sett->getContentSize().width / 2, visibleSize.height / 2 - sett->getContentSize().height / 2));
	toggle1->setPosition(Point(visibleSize.width / 2 - sett->getContentSize().width / 2, visibleSize.height / 2 - sett->getContentSize().height / 2 * 3));
	item1->setPosition(Point(0, -item1->getContentSize().height));
	quitItem->setPosition(Point(0, -item1->getContentSize().height*2));

	auto manu = Menu::create(item1, quitItem, toggle1, sett, NULL);

	this->addChild(manu, 2);

	editBoxUserName = EditBox::create(Size(240, 84), Scale9Sprite::create("EditBox.jpg"));
	editBoxUserName->setMaxLength(15);
	editBoxUserName->setFontColor(Color3B::BLACK);
	editBoxUserName->setFontSize(40);
	editBoxUserName->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	editBoxUserName->setPlaceHolder("   username");
	editBoxUserName->setPlaceholderFontSize(40);
	editBoxUserName->setPosition(Point(visibleSize.width/2, visibleSize.height/2 + 40));
	this->addChild(editBoxUserName, 2);

	auto luobu = Sprite::create("robbat/rob0.png");
	luobu->setScale(3.0f);
	luobu->setPosition(Vec2(visibleSize.width + luobu->getContentSize().width*3/2, visibleSize.height/2));
	auto moveto = MoveTo::create(7.0f, Point(- luobu->getContentSize().width*3/2, visibleSize.height/2));
	
	auto animation = Animation::create();
	for (int i = 0; i <= 6; i++) {
		char x[20];
		sprintf(x, "rob%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(x));
	}
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(10);
	auto animate = Animate::create(animation);
	
	luobu->runAction(Spawn::create(moveto, animate, NULL));
	this->addChild(luobu, 1);

	auto bgspr = Sprite::create("SettingStar/HelloWorldBack.png");
	this->addChild(bgspr, -1);
	bgspr->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

	auto dic = Dictionary::createWithContentsOfFile("text.xml");
	auto GameName = Label::create(dic->valueForKey("GameName")->getCString(), "fonts/luobo.ttf", 200);
	this->addChild(GameName);
	GameName->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
	auto LabelMove = MoveTo::create(1.4f, Point(visibleSize.width/2, visibleSize.height-GameName->getContentSize().height*2/3));
	GameName->runAction(LabelMove);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	string userName = editBoxUserName->getText();
	if (userName == "") {
		return;
	}

	Internet::getInstance()->GetTheUser(editBoxUserName->getText());

	auto sprite = Sprite::create();
	auto animation = Animation::create();
	for (int i = 1; i < 107; i++) {
		char x[30];
		sprintf(x, "load1 (%d).png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(x));
	}
	animation->setDelayPerUnit(0.05);
	animation->setLoops(1);
	auto animate = Animate::create(animation);
	auto callfunc = CallFunc::create(this, callfunc_selector(HelloWorld::toMainGame1));
	auto delaytime = DelayTime::create(0.1f);
	sprite->runAction(Sequence::create(animate, delaytime, callfunc, NULL));
	sprite->setPosition(Point(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height / 2));
	sprite->setScale(2);
	this->addChild(sprite, 3);

}


void HelloWorld::open_Music(cocos2d::Ref * pSender)
{
	auto item = (MenuItemToggle*)pSender;
	if (item->getSelectedIndex() == 0) {
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
	else
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	
}


void HelloWorld::ToSetting()
{
	Director::getInstance()->pushScene(Setting::createScene());
}


float HelloWorld::getAngle(float OriX, float OriY, float FinX, float FinY)
{
	float fEndX = FinX - OriX;
	float fEndY = FinY - OriY;
	float fLen = sqrt(fEndX * fEndX + fEndY * fEndY);
	float fAngle = acos(fEndY / fLen);
	fAngle = fAngle * (360.0 / PI);
	return fAngle;
}

void HelloWorld::toMainGame1()
{
	auto scene = MainGame1::createScene();
	Director::getInstance()->replaceScene(scene);
}

void HelloWorld::quitGame()
{
	SimpleAudioEngine::getInstance()->playEffect("Windows Shutdown.wav");
	Director::getInstance()->end();
}

void HelloWorld::onEnter()
{
	Scene::onEnter();
	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
		toggle1->setSelectedIndex(0);
	}
	else
	{
		toggle1->setSelectedIndex(1);
	}
}