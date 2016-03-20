#pragma once
#ifndef __SCENE_MANGER_H__
#define __SCENE_MANGER_H__

#include "GlobalDefine.h"
#include "cocos2d.h"

USING_NS_CC;


/******************************************* 场景类型枚举 *****************************************/

enum class SceneType
{
	en_None,					// 空场景
	en_Splash_Scene,			// 过渡场景
	en_Start_Scene,				// 开始场景
	en_Tollgate_Scene,			// 关卡场景
	en_Select_Tollgate_Scene,	// 选关场景
	en_Start_Animation_Scene,	// 开始动画场景

};	// SceneType


/************************************************ 场景管理器 *****************************************/

class SceneManager : public Ref
{
public:

	/** 
	 *	功能：创建单例
	 *	_TYPE_:单例类型
	 *	_INSTANCE_NAME_:单例名
	**/
	CREATE_INSTANCE(SceneManager, m_sceneManager);

	virtual ~SceneManager();

	virtual bool init();

	/* 改变当前场景类型 */
	void changeCurSceneType(SceneType type);

protected:
	/* 切换场景 */
	virtual void switchScene();

	/* 当前场景类型 */
	CC_SYNTHESIZE(SceneType, m_curSceneType, CurSceneType);

private:
	SceneManager();
};

#endif // !__SCENE_MANGER_H__

