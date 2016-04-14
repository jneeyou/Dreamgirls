#pragma once
#ifndef __TOLLGATE_LOGIC_LAYER_H__
#define __TOLLGATE_LOGIC_LAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace ui;

class Player;
/*************************************************** 关卡逻辑层 *******************************************/

class TollgateLogicLayer : public Layer
{
public:
	TollgateLogicLayer();
	~TollgateLogicLayer();

	CREATE_FUNC(TollgateLogicLayer);

	virtual bool init();

	/* 绑定图层 */
	void bindLayer(Node* layer);

	/* 绑定玩家 */
	void bindPlayer(Player* player);

	/* 设置控件 */
	void setControlLayer();

	/* 获得图层 */
	Node* getLayer() {return m_layer; }

private:
	/* 图层对象 */
	Node* m_layer;

	/* 玩家对象 */
	Player* m_player;

	/* 子控件 */

	// 分数面板
	TextBMFont* m_scoreLabel;	

	// 按钮
	Button* rightMoveBtn;
	Button* jumpBtn;
	Button* pauseBtn;
};

#endif // !__TOLLGATE_LOGIC_LAYER_H__
