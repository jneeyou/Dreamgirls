#pragma once

#ifndef __MONSTER_MANAGER_H__
#define __MONSTER_MANAGER_H__

#include "cocos2d.h"
#include "Monster.h"
#include "GlobalDefine.h"
USING_NS_CC;

/****************************************** 怪物管理器 *********************************************/

#define MAX_MONSTER_NUM 10	//怪物最大数量

class MonsterManager : public Node
{
public:
	virtual bool init();
	CREATE_INSTANCE(MonsterManager,m_monsterManager);

	virtual void update(float dt);	/* 重写update函数 */

	void bindPlayer(Player* player);	/* 绑定玩家对象 */

	Monster* createMonsterByPosAndName(Vec2& pos, std::string& name);			/* 创建怪物对象 */

private:
	Vector<Monster*> m_monsterArr;	/* 存放怪物列表 */
	Player* m_player;				/* 玩家对象 */
};

#endif // !__MONSTER_MANAGER_H__
