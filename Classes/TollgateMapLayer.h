#pragma once
#ifndef __TOLLGATE_MAP_LAYER_H__
#define __TOLLGATE_MAP_LAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
using namespace cocostudio::timeline;
using namespace ui;

/*************************************************** �ؿ���ͼ�� *******************************************/

class TollgateMapLayer : public Layer
{
public:
	TollgateMapLayer();
	~TollgateMapLayer();

	CREATE_FUNC(TollgateMapLayer);

	virtual bool init();

	/* �󶨵�ͼ */
	void bindMap(experimental::TMXTiledMap* map);

	/* ���ص�ͼ */
	experimental::TMXTiledMap* getMap() { return m_map; }

protected:
	/* ���ÿؼ� */
	void setControlLayer();

	/* �ƶ���ͼ */
	void moveMap(float dt);

	/* �������ж������� */
	void createAllMonsterOfObjectLayer();

	/* ���ݶ���㴴������ */
	void createMonsterByObjLayer(TMXObjectGroup* group);

private:
	/* ��ͼ */
	experimental::TMXTiledMap* m_map;

	/* ���ж��������б� */
	ValueMap m_objPropList;

};

#endif // !__TOLLGATE_MAP_LAYER_H__
