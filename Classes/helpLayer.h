#pragma once
#ifndef __HELP_LAYER_H__
#define __HELP_LAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "EnumStrKey.h"

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace ui;

/*************************************************** 帮助层 *******************************************/

class HelpLayer : public Layer
{
public:
	HelpLayer();
	~HelpLayer();

	CREATE_FUNC(HelpLayer);

	virtual bool init();

	/* 获得背景层 */
	Node* getBgLayer() { return m_bgLayer; }

	/* 通过csv文件子项key设置界面内容 */
	void setTextByCsv(const char* csvFile, EnumStrKey key);

protected:
	/* 设置控件 */
	void setControlLayer();

private:
	Node* m_bgLayer;

	Text* m_text;
};

#endif // !__HELP_LAYER_H__
