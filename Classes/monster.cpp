#include "monster.h"
#include "SimpleAudioEngine.h"
#include "ArmsManager.h"
#include "MainGame2.h"

USING_NS_CC;
using namespace CocosDenshion;

int Monster::Speeds[] = { 1,1,2,2,2,3 };
int Monster::Hps[] = { 100, 180, 100, 150, 150, 200 };

bool Monster::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
    return true;
}

int Monster::getSpeed()
{
	return this->speed;
}

int Monster::getHp()
{
	return this->Hp;
}

void Monster::setHp(int newHp)
{
	if (newHp <= 0)
	{
		newHp = 0;
		
		MainGame2::grade++;

		SimpleAudioEngine::getInstance()->playEffect("Windows Critical Stop.wav");

		ArmsManage::getInstance()->eraseMonster(this);

		auto animation = Animation::create();
		for (int i = 4; i >= 1; i--) {
			char x[20];
			sprintf(x, "die%d.png", i);
			animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(x));
		}
		animation->setDelayPerUnit(0.1f);
		animation->setLoops(1);
		Animate* animate = Animate::create(animation);
		auto callfun = CallFunc::create(this, callfunc_selector(Monster::removeMyself));
		auto sequence = Sequence::create(animate, callfun, NULL);
		this->runAction(sequence);

	}
	progress->runAction(ProgressTo::create(0.01f, (newHp*1.0 / Hps[MonsterNum-1]) * 100));
	this->Hp = newHp;
}

void Monster::setSpped(int newSpeed)
{
	this->speed = newSpeed;
}

int Monster::getNum()
{
	return MonsterNum;
}

Monster* Monster::createMonster()
{
	Monster* monster = new Monster();
	if (monster && monster->init() ) {
		monster->autorelease();
		monster->initMonster();

		return monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}

void Monster::initMonster()
{
	// 创建随机数
	srand((int)time(0));
	MonsterNum = (rand() % 6) + 1;

	Hp = Hps[MonsterNum-1];	//设置HP
	speed = Speeds[MonsterNum - 1]; // 设置速度

	// 添加贴图
	char x[20];
	sprintf(x, "mons/mons%d.png", this->getNum());
	//this->setTexture(x);
	this->initWithFile(x);
	auto size = this->getTexture()->getContentSize();

	// 添加进度条当作血条
	auto progressSprite = Sprite::create("Hp.png");
	progress = ProgressTimer::create(progressSprite);
	progress->setPosition(Point(size.width / 2, size.height + 10)); // 设置 进度条的位置在 怪兽 上面
	this->addChild(progress);
	progress->setType(ProgressTimer::Type::BAR);// 设置 进图条为条形
	progress->setBarChangeRate(Point(1, 0));// 设置 只影响x轴，不影响y轴
	progress->setMidpoint(Point(0, 0));
	progress->runAction(ProgressTo::create(0.01f, 100));
}

void Monster::removeMyself()
{
	this->removeFromParentAndCleanup(true);

}

