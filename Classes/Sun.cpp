#include "Sun.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

int Sun::ATTs[4] = { 0, 40, 60, 90 };
float Sun::angle = 360.0/8;

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Sun::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }

    return true;
}

Sun * Sun::createSun()
{

	auto sun = new Sun();
	if (sun && sun->init()) {
		sun->autorelease();
		sun->initSun();
		return sun;
	}
	CC_SAFE_DELETE(sun);
	return NULL;
}


void Sun::shootIt()
{
	auto animate = CallFunc::create(this, callfunc_selector(Sun::runAnimate));
	auto rotate = RotateBy::create(0.1f, angle);
	auto callfunc = CallFunc::create(this, callfunc_selector(Sun::removePao));
	auto s = Spawn::create(animate, rotate, NULL);
	auto sleep = 
	this->runAction(Sequence::create(animate, rotate, DelayTime::create(0.1f * level), callfunc, NULL));
}

void Sun::runAnimate()
{
	auto size = this->getTexture()->getContentSize();
	sprie = Sprite::create();
	sprie->setPosition(Point(size.width / 2, size.height / 2));

	auto animation = Animation::create();
	for (int i = 1; i <= (level + 2); i++) {
		char x[30];
		sprintf(x, "arms/2/sun%d.png", i);
		CCLOG("%s", x);
		
		//animation->addSpriteFrameWithFileName(x);
		animation->addSpriteFrameWithFile(x);

	}
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	auto animate = Animate::create(animation);
	this->addChild(sprie);
	auto callfunc = CallFuncN::create(this, callfuncN_selector(Sun::removeAnimate));
	sprie->runAction(Sequence::create(animate, callfunc, NULL));
}

void Sun::removePao()
{
	sprie->removeFromParentAndCleanup(true);
	sprie = NULL;
}

void Sun::addLevel()
{
	this->level++;
	if (level > 3) {
		return;
	}
	char x[30];
	sprintf(x, "arms/2/level%d.png", level);
	spr->setScale(1.2);
	this->setTexture(x);
}

int Sun::getLevel()
{
	return level;
}

void Sun::removeAnimate(Node * node)
{
	node->stopAllActions();
	node->removeFromParentAndCleanup(true);
}

void Sun::initSun()
{
	this->initWithFile("arms/2/level1.png");
	auto size = this->getTexture()->getContentSize();
	spr = Sprite::create("arms/2/di.png");
	spr->setPosition(Point(size.width / 2, size.height / 2));
	this->addChild(spr, -1);
	this->level = 1;
}

