#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "BaseEntity.h"
#include "GlobalDefine.h"

class Player;

/*********************************************** ������ ************************************************/

class Monster : public BaseEntity
{
public:
	Monster();
	~Monster();

	CREATE_FUNC(Monster);
	virtual bool init();

	/* ͨ��csv�����ļ����� */
	CREATE_FUNC_0(Monster, const char);
	virtual bool init(const char* csvFilePath);

	virtual bool isCollide(BaseEntity* player) override;

	/* ͨ�����ֺ�λ�ô������� */
	static Monster* createMonsterByPosAndName(Vec2& pos, std::string& name);

	/* ���ù������� */
	void setMonsterProperties(int iRow, const char* csvFilePath);

protected:
	CC_SYNTHESIZE(int, m_monsterAck, MonsterAck);	// ���﹥����

};

#endif // !__MONSTER_H__
