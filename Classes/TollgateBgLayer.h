#pragma once
#ifndef __TOLLGATE_BG_LAYER_H__
#define __TOLLGATE_BG_LAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace ui;

/*************************************************** �ؿ����� *******************************************/

class TollgatBgLayer : public Layer
{
public:
	TollgatBgLayer();
	~TollgatBgLayer();

	CREATE_FUNC(TollgatBgLayer);

	virtual bool init();

	/* ��ͼ�� */
	void bindLayer(Node* layer);

	/* ���ñ�����ɫ */
	void setBgColor(Color4B& color);

	/* ���ö���������ɫ */
	void setTopBgColor(Color4B& color);

	/* ����������ɫ */
	void setMoonColor(Color4B& color);

protected:
	/* ���ÿؼ� */
	void setControlLayer();

	/* �ƶ����� */
	void moveBg(float dt);	

	/* ��ͼ�ƶ��ٶ� */
	CC_SYNTHESIZE(int, m_speed, iSpeed);

	/* �����ƶ�������Ϣ */
	void getMoveBgMsg(Ref* pSender);

	/* �ƶ���ͼ */
	void startMoveBg();

	/* ֹͣ�ƶ� */
	void stopMoveBg();

private:
	/* ͼ����� */
	Node* m_layer;

	/* �ӿؼ� */
	Sprite* bg_one;	// �ײ�����1
	Sprite* bg_one_topBg; // �ײ�����1�ڵı���
	Sprite* bg_two;	// �ײ�����2
	Sprite* bg_two_topBg; // �ײ�����2�ڵı���
	Sprite* moon; // ����

	Sprite* bg_top; // ��������
	Vector<Sprite*> m_chList; // ���������ĺ����б�

	int cnt;	// �ƶ�����
};

#endif // !__TOLLGATE_BG_LAYER_H__
