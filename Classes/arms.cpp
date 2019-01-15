#include "arms.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

int Arms::ATTs[4] = { 0, 60, 80, 120 };

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Arms::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
    return true;
}

Arms * Arms::createArms(int num)
{
	auto arms = new Arms();
	if (arms && arms->init()) {
		arms->autorelease();
		arms->initArm(num);
		return arms;
	}
	return NULL;
}

void Arms::initArm(int num)
{
	this->num = num;
	char x[30] ;
	sprintf(x, "arms/%d/level1.png", num);
	this->initWithFile(x);
	sprintf(x, "arms/%d/di.png", num);

	auto size = this->getTexture()->getContentSize();
	auto spr = Sprite::create(x);
	spr->setPosition(size.width / 2+1, size.height / 2-5);
	this->setScale(1.5f);
	this->addChild(spr, -1);
	level = 1;
	shoot = false;
}

void Arms::runRotate(int angle)
{
	auto rotate = RotateTo::create(0.5f, angle);
	this->runAction(rotate);
}

void Arms::shootIt(Point point)
{
	auto size = this->getTexture()->getContentSize();
	char x[30];
	sprintf(x, "arms/%d/pao%d.png", num, level);
	CCLOG(x);
	sprie = Sprite::create(x);
	sprie->setPosition(Point(size.width / 2 + 1, size.height / 2 - 5));
	
	auto move = MoveTo::create(0.4f - 0.1*level, point);
	auto callfunc = CallFunc::create(this, callfunc_selector(Arms::removePao));
	sprie->runAction(Sequence::create(move, callfunc, NULL));
	this->addChild(sprie);

}

void Arms::addLevel()
{
	++level;
	if (level > 3)
		return;
	char x[30];
	sprintf(x, "arms/%d/level%d.png", num, level);
	this->setTexture(x);
}

int Arms::getLevel()
{
	return level;
}

void Arms::removePao()
{
	sprie->removeFromParentAndCleanup(true);
	sprie = NULL;
}

void Arms::stopShoot()
{

}

