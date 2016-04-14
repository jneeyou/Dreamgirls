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
/*************************************************** �ؿ��߼��� *******************************************/

class TollgateLogicLayer : public Layer
{
public:
	TollgateLogicLayer();
	~TollgateLogicLayer();

	CREATE_FUNC(TollgateLogicLayer);

	virtual bool init();

	/* ��ͼ�� */
	void bindLayer(Node* layer);

	/* ����� */
	void bindPlayer(Player* player);

	/* ���ÿؼ� */
	void setControlLayer();

	/* ���ͼ�� */
	Node* getLayer() {return m_layer; }

private:
	/* ͼ����� */
	Node* m_layer;

	/* ��Ҷ��� */
	Player* m_player;

	/* �ӿؼ� */

	// �������
	TextBMFont* m_scoreLabel;	

	// ��ť
	Button* rightMoveBtn;
	Button* jumpBtn;
	Button* pauseBtn;
};

#endif // !__TOLLGATE_LOGIC_LAYER_H__
