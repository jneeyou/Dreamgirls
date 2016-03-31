#include "MonsterManager.h"

MonsterManager::MonsterManager()
{
	m_monsterList.clear();
}

MonsterManager::~MonsterManager()
{
}

void MonsterManager::init()
{
}

cocos2d::Vector<Monster*>& MonsterManager::getMonsterList()
{
	return m_monsterList;
}
