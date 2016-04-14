#pragma once
#ifndef __SETTING_LAYER_H__
#define __SETTING_LAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace ui;

/*************************************************** 设置层 *******************************************/

class SettingLayer : public Layer
{
public:
	SettingLayer();
	~SettingLayer();

	CREATE_FUNC(SettingLayer);

	virtual bool init();

	virtual void onEnter() override;
	
	/* 获得背景层 */
	Node* getBgLayer() { return m_bgLayer; }

protected:
	/* 设置控件 */
	void setControlLayer();

	/* 按钮回调 */
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
