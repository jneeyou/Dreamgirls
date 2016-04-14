#pragma once
#ifndef __TOLLGATE_SCENE_H__
#define __TOLLGATE_SCENE_H__

#include "BaseScene.h"
#include "TollgateLogicLayer.h"
#include "TollgateBgLayer.h"
#include "TollgateMapLayer.h"
#include "TollgateSplashLayer.h"

class Player;

/*************************************************** 关卡场景 *******************************************/

class TollgateScene : public BaseScene
{
public:
	TollgateScene();
	~TollgateScene();

	CREATE_FUNC_0(TollgateScene, const char);
	static Scene* createScene(const char* filepath);

	virtual bool init(const char* filePath) override;

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	virtual void update(float dt);

protected:
	virtual void setControllerInBgLayer() override;

	void addPlayer(experimental::TMXTiledMap* tiledMap);	// 添加玩家

	void firstEnterGame();	// 第一次进入游戏

	void onEnter() override;

	void loadMapResurce(); // 载入地图资源

	/* 图片加载回调函数 */
	void imageLoadCallFunc(Texture2D* texture);

private:
	Player* m_player;	// 玩家对象

	TollgateLogicLayer* m_logicLayer; // 逻辑层
	TollgatBgLayer* m_bgLayer;		 // 背景层
	TollgateMapLayer* m_mapLayer;    // 地图层
	TollgateSplashLayer* m_spalshLayer;  // 过渡层

	int m_curLevel;		// 当前关卡

	int m_loadResCnt;	// 载入资源计数
};

#endif // !__TOLLGATE_SCENE_H__
