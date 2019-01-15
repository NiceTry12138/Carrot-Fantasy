#pragma execution_character_set("utf-8")
#include "MainGame1.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainGame1::createScene()
{
    return MainGame1::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainGame1::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	this->time = 3;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto BGIMG = Sprite::create("SettingStar/BackGround3.png");
	this->addChild(BGIMG);
	BGIMG->setPosition(Point(visibleSize.width/2, visibleSize.height/2));

	auto dic = Dictionary::createWithContentsOfFile("text.xml");
	welCome = Label::create();

	BestGrade = Label::create();

	if (Internet::getInstance()->getBestGrade() != "error") {
		if (Internet::getInstance()->getBestGrade() == "-1") {
			char x[30];
			sprintf(x, "%s %s", dic->valueForKey("newUser")->getCString(), Internet::getInstance()->getTheUserName().c_str());
			//CCLOG("%s", x);
			welCome->setString(x);

			BestGrade->setString(dic->valueForKey("NewGrade")->getCString());

		}
		else {
			char x[30];
			sprintf(x, "%s %s", dic->valueForKey("welcome")->getCString(), Internet::getInstance()->getTheUserName().c_str());
			//CCLOG("%s", x);
			welCome->setString(x);
			BestGrade->setString((dic->valueForKey("BestGrade")->getCString()+Internet::getInstance()->getBestGrade()).c_str());
		}
	}
	else {
		char x[30];
		sprintf(x, "%s %s", dic->valueForKey("error")->getCString(), Internet::getInstance()->getTheUserName().c_str());
		//CCLOG("%s", x);
		BestGrade->setString(dic->valueForKey("NewGrade")->getCString());
		welCome->setString(x);
	}

	this->addChild(BestGrade);
	BestGrade->setSystemFontSize(15);
	BestGrade->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
	welCome->setSystemFontSize(15);

	welCome->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
	this->addChild(welCome, 1);
    
	auto welComeMove = MoveTo::create(1.5f, Point(visibleSize.width/2, visibleSize.height/2 + welCome->getContentSize().height*6));
	auto scaleto = ScaleTo::create(1.5f, 6.0);
	welCome->runAction(Spawn::create(welComeMove, scaleto, NULL));

	playStar = Label::create();
	playStar->setSystemFontSize(15);
	playStar->setString(dic->valueForKey("paly")->getCString());
	playStar->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	auto playStarMove = MoveTo::create(1.5f, Point(visibleSize.width / 2, visibleSize.height / 2 - welCome->getContentSize().height  * 6));
	this->addChild(playStar, 1);
	playStar->runAction(Spawn::create(playStarMove, scaleto->clone(), NULL));
	BestGrade->runAction(scaleto->clone());

	this->scheduleOnce(SEL_SCHEDULE(&MainGame1::startSchedule), 3.0f);

    return true;
}


void MainGame1::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}

void MainGame1::changeToMainGame()
{
	auto scene = MainGame2::createScene();
	Director::getInstance()->replaceScene(scene);
}

void MainGame1::timeCount(float f)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (this->time == 0) {
		this->changeToMainGame();
	}
	if (this->time == 3) {
		welCome->removeFromParentAndCleanup(true);
		playStar->removeFromParentAndCleanup(true);
		BestGrade->removeFromParentAndCleanup(true);
	}

	countTIme = Label::create();
	countTIme->setString(String::createWithFormat("%d", this->time)->getCString());
	this->addChild(countTIme);
	countTIme->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	countTIme->setSystemFontSize(15);
	auto scaleto = ScaleTo::create(0.6f, 8.0);
	countTIme->runAction(Sequence::create(scaleto, CallFunc::create(this, callfunc_selector(MainGame1::removeCountTime)), NULL));

	this->time--;
}

void MainGame1::removeCountTime()
{
	countTIme->removeFromParentAndCleanup(true);
}

void MainGame1::startSchedule(float f)
{
	this->unschedule(SEL_SCHEDULE(&MainGame1::startSchedule));
	this->schedule(SEL_SCHEDULE(&MainGame1::timeCount), 1.2f);
}
