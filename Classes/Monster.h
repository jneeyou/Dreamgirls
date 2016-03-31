#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "BaseEntity.h"
#include "GlobalDefine.h"

/*********************************************** ������ ************************************************/

class Monster : public BaseEntity
{
public:
	Monster();
	~Monster();

	/* ͨ��csv�����ļ����� */
	CREATE_FUNC_0(Monster, const char);
	virtual bool init(const char* csvFilePath);

protected:
	CC_SYNTHESIZE(int, m_monsterAck, MonsterAck);	// ���﹥����

};

#endif // !__MONSTER_H__
