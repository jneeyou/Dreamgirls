#pragma once

#ifndef __MONSTER_MANAGER_H__
#define __MONSTER_MANAGER_H__

#include "cocos2d.h"
#include "Monster.h"
#include "GlobalDefine.h"
USING_NS_CC;

/****************************************** ��������� *********************************************/

#define MAX_MONSTER_NUM 10	//�����������

class MonsterManager : public Node
{
public:
	virtual bool init();
	CREATE_INSTANCE(MonsterManager,m_monsterManager);

	virtual void update(float dt);	/* ��дupdate���� */

	void bindPlayer(Player* player);	/* ����Ҷ��� */

	Monster* createMonsterByPosAndName(Vec2& pos, std::string& name);			/* ����������� */

private:
	Vector<Monster*> m_monsterArr;	/* ��Ź����б� */
	Player* m_player;				/* ��Ҷ��� */
};

#endif // !__MONSTER_MANAGER_H__
