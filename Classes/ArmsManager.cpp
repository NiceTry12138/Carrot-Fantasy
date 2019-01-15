#include "ArmsManager.h"

ArmsManage* ArmsManage::armsManage = NULL;

ArmsManage * ArmsManage::getInstance()
{
	if (armsManage == NULL) {
		armsManage = new ArmsManage();
	}
	return armsManage;
}

void ArmsManage::addPao(Arms* pao)
{
	Paos.pushBack(pao);
}

void ArmsManage::addSun(Sun* sun)
{
	Suns.pushBack(sun);
}

void ArmsManage::addMonster(Monster* monster)
{
	Monsters.pushBack(monster);
}

void ArmsManage::erasePao(Arms * pao)
{
	Paos.eraseObject(pao);
}

void ArmsManage::eraseSun(Sun * sun)
{
	Suns.eraseObject(sun);
}

void ArmsManage::eraseMonster(Monster * monster)
{
	Monsters.eraseObject(monster);
}

Vector<Arms*>* ArmsManage::getPaos()
{
	return &Paos;
}

Vector<Sun*>* ArmsManage::getSuns()
{
	return &Suns;
}

Vector<Monster*>* ArmsManage::getMonster()
{
	return &Monsters;
}
