#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "BaseEntity.h"
#include "GlobalDefine.h"

/************************************************* 玩家类 **********************************************/

class Player : public BaseEntity
{
public:
	Player();
	~Player();

	/* 通过csv配置文件创建 */
	CREATE_FUNC_0(Player, const char);

	virtual bool init(const char* csvFilePath);

protected:
	/* 跑 */
	void onRun();

	/* 走 */
	void onWalk();

	/* 跳 */
	void onJump();

	/* 抓 */
	void onCatch ();

	/* 攻击 */
	void onAttack();

	/* 增加生命 */
	void onIncreateLife(int lifeValue);

	/* 获得道具 */
	void onGetTool();

	/* 使用道具 */
	void onUseTool();

protected:
	CC_SYNTHESIZE(int, m_curAct, CurAct);						// 当前攻击力
	CC_SYNTHESIZE(int, m_curWalkDistance, CurWalkDistance);		// 已走距离

};

#endif // !__PLAYER_H__
