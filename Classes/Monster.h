#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "BaseEntity.h"
#include "GlobalDefine.h"

class Player;

/*********************************************** 怪物类 ************************************************/

class Monster : public BaseEntity
{
public:
	Monster();
	~Monster();

	CREATE_FUNC(Monster);
	virtual bool init();

	/* 通过csv配置文件创建 */
	CREATE_FUNC_0(Monster, const char);
	virtual bool init(const char* csvFilePath);

	virtual bool isCollide(BaseEntity* player) override;

	/* 通过名字和位置创建怪物 */
	static Monster* createMonsterByPosAndName(Vec2& pos, std::string& name);

	/* 设置怪物属性 */
	void setMonsterProperties(int iRow, const char* csvFilePath);

protected:
	CC_SYNTHESIZE(int, m_monsterAck, MonsterAck);	// 怪物攻击力

};

#endif // !__MONSTER_H__
