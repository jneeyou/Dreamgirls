#pragma once
#ifndef __SETTING_LAYER_H__
#define __SETTING_LAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace ui;

/*************************************************** ���ò� *******************************************/

class SettingLayer : public Layer
{
public:
	SettingLayer();
	~SettingLayer();

	CREATE_FUNC(SettingLayer);

	virtual bool init();

	virtual void onEnter() override;
	
	/* ��ñ����� */
	Node* getBgLayer() { return m_bgLayer; }

protected:
	/* ���ÿؼ� */
	void setControlLayer();

	/* ��ť�ص� */
	void menuCallback(Ref* ref,Widget::TouchEventType type);

private:
	Node* m_bgLayer;

	Button* helpBtn;
	Button* openMusicBtn;
	Button* openEffectBtn;
	Button* closeEffectBtn;
	Button* closeMusicBtn;

	bool m_musicOn;
	bool m_effectOn;
};

#endif // !__SETTING_LAYER_H__
