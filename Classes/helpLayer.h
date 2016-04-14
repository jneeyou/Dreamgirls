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

/*************************************************** ������ *******************************************/

class HelpLayer : public Layer
{
public:
	HelpLayer();
	~HelpLayer();

	CREATE_FUNC(HelpLayer);

	virtual bool init();

	/* ��ñ����� */
	Node* getBgLayer() { return m_bgLayer; }

	/* ͨ��csv�ļ�����key���ý������� */
	void setTextByCsv(const char* csvFile, EnumStrKey key);

protected:
	/* ���ÿؼ� */
	void setControlLayer();

private:
	Node* m_bgLayer;

	Text* m_text;
};

#endif // !__HELP_LAYER_H__
