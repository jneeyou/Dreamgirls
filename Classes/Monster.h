#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "BaseEntity.h"
#include "GlobalDefine.h"

/*********************************************** 怪物类 ************************************************/

class Monster : public BaseEntity
{
public:
	Monster();
	~Monster();

	/* 通过csv配置文件创建 */
	CREATE_FUNC_0(Monster, const char);
	virtual bool init(const char* csvFilePath);

protected:
	CC_SYNTHESIZE(int, m_monsterAck, MonsterAck);	// 怪物攻击力

};

#endif // !__MONSTER_H__
