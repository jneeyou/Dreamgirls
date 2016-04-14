#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "BaseEntity.h"
#include "GlobalDefine.h"
#include "cocostudio\CocoStudio.h"

using namespace cocostudio::timeline;

typedef experimental::TMXTiledMap ETMXTileMap;
typedef experimental::TMXLayer ETMXLayer;

/************************************************* 玩家类 **********************************************/

class Player : public BaseEntity
{
public:
	Player();
	~Player();

	/* 通过csv配置文件创建 */
	CREATE_FUNC_0(Player, const char);

	virtual bool init(const char* csvFilePath);

	/* 跑 */
	void run(bool isLeft);

	/*停止跑 */
	void stopRun();

	/* 跳 */
	void jump(int high);

	/* 设置主角视图位置 */
	void setViewPointByPlayer();

	/* 设置目标位置 */
	virtual void setTagPosition(int x, int y);

	/* 设置地图 */
	void setTiedMap(experimental::TMXTiledMap* map);

	void update(float dt);

protected:
	/* 走 */
	void onWalk();

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

	/* 绑定精灵 */
	virtual void onBindSprite() override;

protected:
	/* 加载玩家动画 */
	void loadPlayerAnimation(const std::string fileName);

	/* 设置玩家属性 */
	void setPlayerProperties(int iRow,const char* csvFilePath);

	/* 移动位置 */
	void movePos(float dt, float dis);

	/* 将像素坐标转换为地图格子坐标 */
	Point tileCoordForPosition(Point pos);

	CC_SYNTHESIZE(int, m_curAct, CurAct);						// 当前攻击力
	CC_SYNTHESIZE(int, m_curWalkDistance, CurWalkDistance);		// 已走距离

	/* 设置是否左移 */
	void setIsLeftMove(bool isLeft);

private:
	/* 时间线动画 */
	ActionTimeline* m_timeline;

	/* 是否左移 */
	bool m_isLeftMove;

	/* 是否回弹 */
	bool m_isRebound;

	/* 地图 */
	experimental::TMXTiledMap* m_map;

	/* 碰撞检测层 */
	experimental::TMXLayer* m_metaLayer;
		
	/* 跑动时间 */
	float runTime;

	/* 跳跃时间 */
	float jumpTime;

	/* 是否在跑 */
	bool m_isRunning;

};

#endif // !__PLAYER_H__
