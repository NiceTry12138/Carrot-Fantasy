#include "MainGame2.h"
#include "SimpleAudioEngine.h"
#include "GameOver.h"
#define PI 3.14159265359
USING_NS_CC;
using namespace CocosDenshion;

int MainGame2::grade = 0;

Scene* MainGame2::createScene()
{
    return MainGame2::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainGame2::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	ArmsManage::getInstance()->getMonster()->clear();
	ArmsManage::getInstance()->getPaos()->clear();
	ArmsManage::getInstance()->getSuns()->clear();

	selectArms = NULL;
	selectSun = NULL;

	this->MonsterNum = 0;
	Monsterspeed = 0.4f;
	creataMonsterTime = 20.0f;
	MenuCreateOrNot = true;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	sun = MenuItemImage::create("Sun.png", "Sun.png", CC_CALLBACK_0(MainGame2::createSun, this));
	pao = MenuItemImage::create("Pao.png", "Pao.png", CC_CALLBACK_0(MainGame2::createPao, this));
	sun->setPosition(Point(-(sun->getContentSize().width / 2 + 5), 0));
	pao->setPosition(Point(+(pao->getContentSize().width / 2 + 5), 0));
	PaoAndSun = Menu::create(pao, sun, NULL);
	PaoAndSun->retain();

	upIt = MenuItemImage::create("update.png", "update1.png", CC_CALLBACK_0(MainGame2::createUp, this));
	closeIt = MenuItemImage::create("exit.png", "exit2.png", CC_CALLBACK_0(MainGame2::createCloas, this));
	upIt->setPosition(Point(0, closeIt->getContentSize().height+5));
	closeIt->setPosition(Point(0, 0));
	MenuIt = Menu::create(closeIt, upIt, NULL);
	MenuIt->retain();

	robbat = Robbat::createRobbat();
	robbat->setPosition(Point(2*30, 6*30));
	robbat->setScale(0.95);
	this->addChild(robbat, 4);
	
	auto BGImg = Sprite::create("SettingStar/BackGround1.png");
	this->addChild(BGImg, -1);
	BGImg->setPosition(Point(visibleSize.width/2, visibleSize.height/2));

	tilemap = TMXTiledMap::create("tilemap/map.tmx");
	this->addChild(tilemap, 1);
	
	this->schedule(SEL_SCHEDULE(&MainGame2::createMonster), 1.0f);

	auto TouchLintener = EventListenerTouchOneByOne::create();

	TouchLintener->onTouchBegan = CC_CALLBACK_2(MainGame2::onTouchBegaan, this);
	TouchLintener->onTouchEnded = CC_CALLBACK_2(MainGame2::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(TouchLintener, this);
	
	auto toSetting = MenuItemImage::create("SettingStar/setIcon.png", "SettingStar/setIcon2.png",CC_CALLBACK_0(MainGame2::toSettingScene, this));
	auto toHome = MenuItemImage::create("SettingStar/home1.png", "SettingStar/home2.png", CC_CALLBACK_0(MainGame2::toHomeScene, this));
	auto jiasu1 = MenuItemImage::create("SettingStar/1bei.png", "SettingStar/1bei.png");
	auto jiasu2 = MenuItemImage::create("SettingStar/2bei.png", "SettingStar/2bei.png");
	auto toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MainGame2::jiaSu, this), jiasu1, jiasu2, NULL);
	auto menu = Menu::create(toggle, toSetting, toHome, NULL);
	this->addChild(menu);
	toSetting->setPosition(Point(-visibleSize.width/2+toSetting->getContentSize().width/2, 0));
	toHome->setPosition(Point(-visibleSize.width/2+toSetting->getContentSize().width + toHome->getContentSize().width/2, 0));
	toggle->setPosition(Point(-visibleSize.width/2 + toggle->getContentSize().width/2, toHome->getContentSize().height));

	this->schedule(SEL_SCHEDULE(&MainGame2::Myupdate), 0.5f);

    return true;
}

void MainGame2::createMonster(float dt)
{
	this->MonsterNum++;
	if (this->MonsterNum == 10) {
		this->Monsterspeed -= 0.02f;
		if (this->Monsterspeed <= 0.05f) {
			this->Monsterspeed = 0.05f;
		}
		this->MonsterNum = 0;
		this->unschedule(SEL_SCHEDULE(&MainGame2::createMonster));
		this->scheduleOnce(SEL_SCHEDULE(&MainGame2::starCreateMonster), 120 * Monsterspeed);
		return;
	}
	auto monster = Monster::createMonster();
	ArmsManage::getInstance()->addMonster(monster);
	monster->setScale(1.3f);
	this->addChild(monster, 2);
	monster->setPosition(Point(60, 690));

	auto move1 = MoveBy::create(3 * Monsterspeed, Point(0, 30 * -3));
	auto move2 = MoveBy::create(13 * Monsterspeed, Point(13 * 30, 0));
	auto move3 = MoveBy::create(3 * Monsterspeed, Point(0, 2 * 30 + 15));
	auto move4 = MoveBy::create(10 * Monsterspeed, Point(10 * 30 + 15, 0));
	auto move5 = MoveBy::create(3 * Monsterspeed, Point(0, -(2 * 30 + 15)));
	auto move6 = MoveBy::create(8 * Monsterspeed, Point(7 * 30 + 15, 0));
	auto move7 = MoveBy::create(3 * Monsterspeed, Point(0, 2 * 30 + 15));
	auto move8 = MoveBy::create(8 * Monsterspeed, Point(7 * 30 + 15, 0));
	auto move9 = MoveBy::create(9 * Monsterspeed, Point(0, -(8 * 30 + 15)));
	auto move10 = MoveBy::create(5 * Monsterspeed, Point(-(6 * 30 + 15), 0));
	auto move11 = MoveBy::create(3 * Monsterspeed, Point(0, 2 * 30 + 15));
	auto move12 = MoveBy::create(8 * Monsterspeed, Point(-(7 * 30 + 15), 0));
	auto move13 = MoveBy::create(3 * Monsterspeed, Point(0, -(2 * 30 + 15)));
	auto move14 = MoveBy::create(5 * Monsterspeed, Point(-5 * 30, 0));
	auto move15 = MoveBy::create(3 * Monsterspeed, Point(0, 2 * 30 + 15));
	auto move16 = MoveBy::create(13 * Monsterspeed, Point(-13 * 30, 0));
	auto move17 = MoveBy::create(3 * Monsterspeed, Point(0, -(2 * 30 + 15)));
	auto move18 = MoveBy::create(8 * Monsterspeed, Point(7 * 30 + 15, -15));
	auto move19 = MoveBy::create(3 * Monsterspeed, Point(0, -(2 * 30 + 15)));
	auto move20 = MoveBy::create(6 * Monsterspeed, Point(6 * 30, -15));
	auto move21 = MoveBy::create(3 * Monsterspeed, Point(0, -(2 * 30 - 15)));
	auto move22 = MoveBy::create(6 * Monsterspeed, Point(5 * 30 + 15, 0));
	auto move23 = MoveBy::create(3 * Monsterspeed, Point(0, 2 * 30 + 15));
	auto move24 = MoveBy::create(7 * Monsterspeed, Point(7 * 30, 0));
	auto move25 = MoveBy::create(3 * Monsterspeed, Point(0, -(2 * 30 + 15)));
	auto move26 = MoveBy::create(6 * Monsterspeed, Point(5 * 30 + 15, 0));
	auto move27 = MoveBy::create(6 * Monsterspeed, Point(0, -6 * 30));
	auto move28 = MoveBy::create(39 * Monsterspeed, Point(-(38 * 30 + 15), 0));
	auto move29 = MoveBy::create(3 * Monsterspeed, Point(0, 3 * 30));

	auto callfunc = CallFuncN::create(this, callfuncN_selector(MainGame2::RobbatHpDown));

	auto moveToFin = Sequence::create(move1, move2, move3, move4, move5, move6, move7, move8, move9, move10, move11, move12, move13, move14, move15, move16, move17, move18, move19, move20, move21, move22, move23, move24, move25, move26, move27, move28, move29, NULL);
	auto junp = JumpBy::create(196 * Monsterspeed, Point(0, 0), 20, 120);

	auto MonsterAction = Spawn::create(moveToFin, junp, NULL);

	monster->runAction(Sequence::create(MonsterAction, callfunc, NULL));


}

void MainGame2::RobbatHpDown(Node* node)
{
	robbat->HpDown();
	if (robbat->GetHp() == 0) {
		CCLOG("Game Over");
		Internet::getInstance()->sendNewUser(Internet::getInstance()->getTheUserName(), MainGame2::grade);
		Director::getInstance()->replaceScene(GameOver::createScene());
	}
	auto mons = (Monster*)node;
	ArmsManage::getInstance()->eraseMonster(mons);
	mons->removeFromParentAndCleanup(true);
}

void MainGame2::starCreateMonster(float dt)
{
	this->schedule(SEL_SCHEDULE(&MainGame2::createMonster), 2.5*Monsterspeed);
}

void MainGame2::toSettingScene()
{
	Director::getInstance()->pushScene(Setting::createScene());
}

void MainGame2::toHomeScene()
{
	Director::getInstance()->getScheduler()->setTimeScale(1.0f);
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void MainGame2::jiaSu(cocos2d::Ref * pSender)
{
	auto toggle = (MenuItemToggle *)pSender;
	if (toggle->getSelectedIndex() == 0) {
		Director::getInstance()->getScheduler()->setTimeScale(1.0f);
	}
	else
	{
		Director::getInstance()->getScheduler()->setTimeScale(2.0f);
	}
}

void MainGame2::createSun()
{
	auto sun = Sun::createSun();
	ArmsManage::getInstance()->addSun(sun);
	sun->setPosition(TouchPoint);
	this->addChild(sun, 4);
	PaoAndSun->removeFromParent();
	MenuCreateOrNot = true;
}

void MainGame2::createPao()
{
	auto pao = Arms::createArms(1);
	ArmsManage::getInstance()->addPao(pao);
	pao->setPosition(TouchPoint);
	pao->setScale(0.9);
	this->addChild(pao, 4);
	PaoAndSun->removeFromParent();
	MenuCreateOrNot = true;
}

void MainGame2::createUp()
{
	if (selectArms != NULL)
	{
		selectArms->addLevel();
		selectArms = NULL;
	}
	else if(selectSun != NULL)
	{
		selectSun->addLevel();
		selectSun = NULL;
	}
	MenuIt->removeFromParent();
}

void MainGame2::createCloas()
{
	MenuIt->removeFromParent();
}

bool MainGame2::onTouchBegaan(Touch * touch, Event * event)
{

	Point point = touch->getLocation();
	if (robbat->getBoundingBox().containsPoint(point)) {
		robbat->runAnimate();
	}


	for (int i = 0; i < ArmsManage::getInstance()->getPaos()->size(); i++) {
		if (ArmsManage::getInstance()->getPaos()->at(i)->getBoundingBox().containsPoint(point)) {
			selectArms = ArmsManage::getInstance()->getPaos()->at(i);
			MenuIt->setPosition(point);
			this->addChild(MenuIt, 6);
			return false;
		}
			
	}
	for (int i = 0; i < ArmsManage::getInstance()->getSuns()->size(); i++) {
		if (ArmsManage::getInstance()->getSuns()->at(i)->getBoundingBox().containsPoint(point)) {
			selectSun = ArmsManage::getInstance()->getSuns()->at(i);
			MenuIt->setPosition(point);
			this->addChild(MenuIt, 6);
			return false;
		}
			
	}
	
	if (inMapLoad(point)) {
		return false;
	}

	return true;
}

void MainGame2::onTouchEnded(Touch * touch, Event * event)
{
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Point point = touch->getLocation();
	

	auto WinSize = Director::getInstance()->getVisibleSize();
	if (MenuCreateOrNot) {
		MenuCreateOrNot = false;
		TouchPoint = touch->getLocation();
		PaoAndSun->setPosition(TouchPoint);
		this->addChild(PaoAndSun, 5);
	}
	else
	{
		PaoAndSun->removeFromParent();
		MenuCreateOrNot = true;
	}
}



void MainGame2::Myupdate(float delta)
{
	auto paosVec = ArmsManage::getInstance()->getPaos();
	auto sunsVec = ArmsManage::getInstance()->getSuns();
	auto monsterVec = ArmsManage::getInstance()->getMonster();
	for (int i = 0; i < paosVec->size(); i++) {
		auto theArm = paosVec->at(i);
		auto theArmPosition = theArm->getPosition();
		for (int j = 0; j < monsterVec->size(); j++) {
			auto theMonster = monsterVec->at(j);
			auto theMonsterPoint = theMonster->getPosition();
			float Raid = getR(theMonsterPoint, theArmPosition);
			if ( Raid <= 120.0f) {
				theMonster->setHp(theMonster->getHp() - Arms::ATTs[theArm->getLevel()]);
				theArm->shootIt(theArm->convertToNodeSpace(theMonsterPoint));
				theArm->runRotate(changeAngle(theArmPosition, theMonsterPoint));
				break;
			}
		}
	}
	for (int i = 0; i < sunsVec->size(); i++) {
		auto theSun = sunsVec->at(i);
		auto thtSunPosition = theSun->getPosition();
		for (int j = 0; j < monsterVec->size(); j++) {
			auto runSunAniamate = true;
			auto theMonster = monsterVec->at(j);
			auto theMonsterPoiont = theMonster->getPosition();
			float Raid = getR(thtSunPosition, theMonsterPoiont);
			if (Raid <= 120.f) {
				theMonster->setHp(theMonster->getHp() - Sun::ATTs[theSun->getLevel()]);
				if (runSunAniamate) {
					runSunAniamate = false;
					theSun->runAnimate();
				}
			}
		}
	}
}

float MainGame2::getR(Point a, Point b)
{
	float theWidth = a.x - b.x;
	float theHeight = a.y - b.y;
	
	return sqrtf(theWidth*theWidth + theHeight * theHeight);
}

float MainGame2::changeAngle(Point a, Point b)
{
	auto fOriginX_Vec = a.x;
	auto fOriginY_Vec = a.y;
	auto fEndX_Vec = b.x;
	auto fEndY_Vec = b.y;
	float fEndX = fEndX_Vec - fOriginX_Vec;
	float fEndY = fEndY_Vec - fOriginY_Vec;
	float fLen = sqrt(fEndX * fEndX + fEndY * fEndY);
	float fAngle = acos(fEndY / fLen);

	if (fEndX < 0)
	{
		fAngle = 2 * PI - fAngle;
	}
	fAngle = (180 / PI) * fAngle;
	return fAngle;
}

bool MainGame2::inMapLoad(Point point)
{
	auto layer = tilemap->getLayer("road");
	
	auto visisize = Director::getInstance()->getVisibleSize();
	//CCLOG("height %f", tilemap->getMapSize().height);

	Vec2 spritecurPos = Vec2(point.x / 30 , tilemap->getMapSize().height - point.y / 30);
	//log("ggggggid %d", layer->getTileGIDAt(spritecurPos));
	if (layer->getTileGIDAt(spritecurPos) != 0) {
		return true;
	}
	return false;
}
