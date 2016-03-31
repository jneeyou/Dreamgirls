#pragma once
#ifndef __MONSTER_MANAGER_H__
#define __MONSTER_MANAGER_H__

#include "cocos2d.h"
#include "Monster.h"

/************************************************************************** 怪物管理器 ****************************************************************/

class MonsterManager : public cocos2d::Ref
{
public:
	MonsterManager();
	~MonsterManager();

	virtual void init();

	/* 获得怪物列表 */
	cocos2d::Vector<Monster*>& getMonsterList();

private:
	cocos2d::Vector<Monster*> m_monsterList;	// 怪物列表
};

#endif // !__MONSTER_MANAGER_H__