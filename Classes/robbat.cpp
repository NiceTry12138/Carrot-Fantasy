#include "robbat.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Robbat::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }

    return true;
}

Robbat* Robbat::createRobbat()
{
	auto robbat = new Robbat();
	if (robbat && robbat->init()) {
		robbat->autorelease();
		robbat->initRobbat();
		return robbat;
	}
	CC_SAFE_DELETE(robbat);
	return NULL;
}

void Robbat::initRobbat()
{
	this->Hp = 10;
	this->initWithFile("robbat/HP10.png");
	this->setScale(1.7f);
}

void Robbat::runAnimate()
{
	if (Hp != 10) {
		return;
	}
	auto animation = Animation::create();
	for (int i = 0; i <= 6; i++) {
		char x[20];
		sprintf(x, "robbat/rob%d.png", i);
		animation->addSpriteFrameWithFileName(x);
	}
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	auto animate = Animate::create(animation);
	this->runAction(animate);
}



void Robbat::HpDown()
{
	Hp--;
	switch (Hp)
	{
	case 9:
		this->setTexture("robbat/HP9.png");
		break;
	case 7:
		this->setTexture("robbat/HP7.png");
		break;
	case 5:
		this->setTexture("robbat/HP5.png");
		break;
	case 3:
		this->setTexture("robbat/HP3.png");
		break;
	case 1:
		this->setTexture("robbat/HP1.png");
		break;
	default:
		break;
	}
}

int Robbat::GetHp()
{
	return this->Hp;
}
