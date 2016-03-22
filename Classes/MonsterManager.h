#pragma once
#ifndef __MONSTER_MANAGER_H__
#define __MONSTER_MANAGER_H__

#include "cocos2d.h"

class Monster;

/************************************************************************** ��������� ****************************************************************/

class MonsterManager : public cocos2d::Ref
{
public:
	MonsterManager();
	~MonsterManager();

	virtual void init();

	/* ��ù����б� */
	Monster* getMonsterList();

private:
	cocos2d::Vector<Monster*> m_monsterList;	// �����б�
};

#endif // !__MONSTER_MANAGER_H__