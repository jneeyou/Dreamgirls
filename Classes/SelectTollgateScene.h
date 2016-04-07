#pragma once
#ifndef __SELECT_TOLLGATE_SCENE_H__
#define __SELECT_TOLLGATE_SCENE_H__

#include "BaseScene.h"

/*************************************************** ѡ�س��� *******************************************/

class SelectTollgateScene : public BaseScene
{
public:
	CREATE_FUNC_0(SelectTollgateScene, const char);
	CREATE_SCENE_0(SelectTollgateScene, const char);

	virtual bool init(const char* filePath) override;

	virtual void update(float dt) override;

protected:
	void setControllerInBgLayer() override;

	/* ����ui */
	void updateUI(bool isLeftSiding,float tm);

	/* �󶨴������� */
	void bindTouchListener();

	/* ���뵱ǰ�ؿ����� */
	void enterCurTollgateScene();

private:
	/* ��ǰѡ��ؿ� */
	int m_iCurTollgate;

	/* ѡ������� */
	float interval_pos;

	/* �Ƿ񻬶� */
	bool m_isSliding;

	/* ������ʼ������λ�� */
	Vec2 m_sPos;
	Vec2 m_ePos;

	/* ������� */
	Rect boundBox;

	/* �����ؿ��� */
	int m_unlockTollgateNum;

	/* ���ؿ��� */
	int m_maxTollgateNum;

	/* ������� */
	int m_actionFlag;

	/* ��������ʱ�� */
	float m_touchTime;

	/* ��ʱ��� */
	bool m_isCountTime;

	/*�ӿؼ� */
	Sprite* lv_left;
	Sprite* lv_right;
	Sprite* lv_center;
	Sprite* slt_bar_yes;

	Button* home_btn;
	Button* setting_btn;
};

#endif // !__SELECT_TOLLGATE_SCENE_H__
