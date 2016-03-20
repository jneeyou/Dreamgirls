#pragma once
#ifndef __SCENE_MANGER_H__
#define __SCENE_MANGER_H__

#include "GlobalDefine.h"
#include "cocos2d.h"

USING_NS_CC;


/******************************************* ��������ö�� *****************************************/

enum class SceneType
{
	en_None,					// �ճ���
	en_Splash_Scene,			// ���ɳ���
	en_Start_Scene,				// ��ʼ����
	en_Tollgate_Scene,			// �ؿ�����
	en_Select_Tollgate_Scene,	// ѡ�س���
	en_Start_Animation_Scene,	// ��ʼ��������

};	// SceneType


/************************************************ ���������� *****************************************/

class SceneManager : public Ref
{
public:

	/** 
	 *	���ܣ���������
	 *	_TYPE_:��������
	 *	_INSTANCE_NAME_:������
	**/
	CREATE_INSTANCE(SceneManager, m_sceneManager);

	virtual ~SceneManager();

	virtual bool init();

	/* �ı䵱ǰ�������� */
	void changeCurSceneType(SceneType type);

protected:
	/* �л����� */
	virtual void switchScene();

	/* ��ǰ�������� */
	CC_SYNTHESIZE(SceneType, m_curSceneType, CurSceneType);

private:
	SceneManager();
};

#endif // !__SCENE_MANGER_H__

