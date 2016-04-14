#pragma once
#ifndef __BASE_SCENE_H__
#define __BASE_SCENE_H__

#include "cocos2d.h"
#include "GlobalDefine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace ui;

/********************************************************* 基类场景 **************************************************/

class BaseScene : public Layer
{
public:
	BaseScene();
	virtual ~BaseScene();

	virtual bool init();
	virtual bool init(const char* filePath);

protected:
	/* 通过文件设置背景层 */
	virtual void setBgLayerByFile(const char* filePath);

	/* 设置背景层控件,子类实现 */
	virtual void setControllerInBgLayer();

	virtual void onEnter() override;

protected:
	Node* bgLayer;	// 背景层
};

#endif // !__BASE_SCENE_H__
