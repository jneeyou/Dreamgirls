#pragma once
#ifndef __TOLLGATE_SCENE_H__
#define __TOLLGATE_SCENE_H__

#include "BaseScene.h"

class Player;

/*************************************************** 关卡场景 *******************************************/

class TollgateScene : public BaseScene
{
public:
	CREATE_FUNC_0(TollgateScene, const char);
	CREATE_SCENE_0(TollgateScene, const char);

	virtual bool init(const char* filePath) override;

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

protected:
	virtual void setControllerInBgLayer() override;

	void addPlayer(TMXTiledMap* tiledMap);	// 添加玩家

	void moveBg(float dt);	// 移动背景

private:
	TextBMFont* m_scoreLabel;	// 分数面板

	Player* m_player;	// 玩家对象

	Sprite* m_bottomBg;
	Sprite* m_topBg;

	Button* rightMoveBtn;
	Button* jumpBtn;
	Button* pauseBtn;
};

#endif // !__TOLLGATE_SCENE_H__
