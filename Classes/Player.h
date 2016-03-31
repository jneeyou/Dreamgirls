#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "BaseEntity.h"
#include "GlobalDefine.h"
#include "cocostudio\CocoStudio.h"

using namespace cocostudio::timeline;

/************************************************* ����� **********************************************/

class Player : public BaseEntity
{
public:
	Player();
	~Player();

	/* ͨ��csv�����ļ����� */
	CREATE_FUNC_0(Player, const char);

	virtual bool init(const char* csvFilePath);

	/* �� */
	void run();

protected:
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
	/* ������Ҷ��� */
	void loadPlayerAnimation(const std::string fileName);

	/* ����������� */
	void setPlayerProperties(const char* csvFilePath);

	CC_SYNTHESIZE(int, m_curAct, CurAct);						// ��ǰ������
	CC_SYNTHESIZE(int, m_curWalkDistance, CurWalkDistance);		// ���߾���

private:
	/* ʱ���߶��� */
	ActionTimeline* m_timeline;

};

#endif // !__PLAYER_H__
