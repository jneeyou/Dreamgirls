#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "BaseEntity.h"
#include "GlobalDefine.h"

/************************************************* ����� **********************************************/

class Player : public BaseEntity
{
public:
	Player();
	~Player();

	/* ͨ��csv�����ļ����� */
	CREATE_FUNC_0(Player, const char);

	virtual bool init(const char* csvFilePath);

protected:
	/* �� */
	void onRun();

	/* �� */
	void onWalk();

	/* �� */
	void onJump();

	/* ץ */
	void onCatch ();

	/* ���� */
	void onAttack();

	/* �������� */
	void onIncreateLife(int lifeValue);

	/* ��õ��� */
	void onGetTool();

	/* ʹ�õ��� */
	void onUseTool();

protected:
	CC_SYNTHESIZE(int, m_curAct, CurAct);						// ��ǰ������
	CC_SYNTHESIZE(int, m_curWalkDistance, CurWalkDistance);		// ���߾���

};

#endif // !__PLAYER_H__
