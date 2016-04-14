#pragma once
#ifndef __TOLLGATE_MAP_LAYER_H__
#define __TOLLGATE_MAP_LAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
using namespace cocostudio::timeline;
using namespace ui;

/*************************************************** 关卡地图层 *******************************************/

class TollgateMapLayer : public Layer
{
public:
	TollgateMapLayer();
	~TollgateMapLayer();

	CREATE_FUNC(TollgateMapLayer);

	virtual bool init();

	/* 绑定地图 */
	void bindMap(experimental::TMXTiledMap* map);

	/* 返回地图 */
	experimental::TMXTiledMap* getMap() { return m_map; }

protected:
	/* 设置控件 */
	void setControlLayer();

	/* 移动地图 */
	void moveMap(float dt);

	/* 创建所有对象层怪物 */
	void createAllMonsterOfObjectLayer();

	/* 根据对象层创建怪物 */
	void createMonsterByObjLayer(TMXObjectGroup* group);

private:
	/* 地图 */
	experimental::TMXTiledMap* m_map;

	/* 所有对象属性列表 */
	ValueMap m_objPropList;

};

#endif // !__TOLLGATE_MAP_LAYER_H__
