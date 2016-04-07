#pragma once
#ifndef __SELECT_TOLLGATE_SCENE_H__
#define __SELECT_TOLLGATE_SCENE_H__

#include "BaseScene.h"

/*************************************************** 选关场景 *******************************************/

class SelectTollgateScene : public BaseScene
{
public:
	CREATE_FUNC_0(SelectTollgateScene, const char);
	CREATE_SCENE_0(SelectTollgateScene, const char);

	virtual bool init(const char* filePath) override;

	virtual void update(float dt) override;

protected:
	void setControllerInBgLayer() override;

	/* 更新ui */
	void updateUI(bool isLeftSiding,float tm);

	/* 绑定触摸监听 */
	void bindTouchListener();

	/* 进入当前关卡场景 */
	void enterCurTollgateScene();

private:
	/* 当前选择关卡 */
	int m_iCurTollgate;

	/* 选择条间距 */
	float interval_pos;

	/* 是否滑动 */
	bool m_isSliding;

	/* 触摸开始、结束位置 */
	Vec2 m_sPos;
	Vec2 m_ePos;

	/* 检测区域 */
	Rect boundBox;

	/* 解锁关卡数 */
	int m_unlockTollgateNum;

	/* 最大关卡数 */
	int m_maxTollgateNum;

	/* 动作标记 */
	int m_actionFlag;

	/* 滑动触摸时间 */
	float m_touchTime;

	/* 计时标记 */
	bool m_isCountTime;

	/*子控件 */
	Sprite* lv_left;
	Sprite* lv_right;
	Sprite* lv_center;
	Sprite* slt_bar_yes;

	Button* home_btn;
	Button* setting_btn;
};

#endif // !__SELECT_TOLLGATE_SCENE_H__
