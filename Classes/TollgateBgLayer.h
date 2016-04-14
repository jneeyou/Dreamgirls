#pragma once
#ifndef __TOLLGATE_BG_LAYER_H__
#define __TOLLGATE_BG_LAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace ui;

/*************************************************** 关卡背景 *******************************************/

class TollgatBgLayer : public Layer
{
public:
	TollgatBgLayer();
	~TollgatBgLayer();

	CREATE_FUNC(TollgatBgLayer);

	virtual bool init();

	/* 绑定图层 */
	void bindLayer(Node* layer);

	/* 设置背景颜色 */
	void setBgColor(Color4B& color);

	/* 设置顶部背景颜色 */
	void setTopBgColor(Color4B& color);

	/* 设置月亮颜色 */
	void setMoonColor(Color4B& color);

protected:
	/* 设置控件 */
	void setControlLayer();

	/* 移动背景 */
	void moveBg(float dt);	

	/* 地图移动速度 */
	CC_SYNTHESIZE(int, m_speed, iSpeed);

	/* 处理移动背景消息 */
	void getMoveBgMsg(Ref* pSender);

	/* 移动地图 */
	void startMoveBg();

	/* 停止移动 */
	void stopMoveBg();

private:
	/* 图层对象 */
	Node* m_layer;

	/* 子控件 */
	Sprite* bg_one;	// 底部背景1
	Sprite* bg_one_topBg; // 底部背景1内的背景
	Sprite* bg_two;	// 底部背景2
	Sprite* bg_two_topBg; // 底部背景2内的背景
	Sprite* moon; // 月亮

	Sprite* bg_top; // 顶部背景
	Vector<Sprite*> m_chList; // 顶部背景的孩子列表

	int cnt;	// 移动次数
};

#endif // !__TOLLGATE_BG_LAYER_H__
