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

/********************************************************* ���ೡ�� **************************************************/

class BaseScene : public Layer
{
public:
	BaseScene();
	virtual ~BaseScene();

	virtual bool init();
	virtual bool init(const char* filePath);

protected:
	/* ͨ���ļ����ñ����� */
	virtual void setBgLayerByFile(const char* filePath);

	/* ���ñ�����ؼ�,����ʵ�� */
	virtual void setControllerInBgLayer();

	virtual void onEnter() override;

protected:
	Node* bgLayer;	// ������
};

#endif // !__BASE_SCENE_H__
