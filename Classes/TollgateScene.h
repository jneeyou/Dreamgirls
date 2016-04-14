#pragma once
#ifndef __TOLLGATE_SCENE_H__
#define __TOLLGATE_SCENE_H__

#include "BaseScene.h"
#include "TollgateLogicLayer.h"
#include "TollgateBgLayer.h"
#include "TollgateMapLayer.h"
#include "TollgateSplashLayer.h"

class Player;

/*************************************************** �ؿ����� *******************************************/

class TollgateScene : public BaseScene
{
public:
	TollgateScene();
	~TollgateScene();

	CREATE_FUNC_0(TollgateScene, const char);
	static Scene* createScene(const char* filepath);

	virtual bool init(const char* filePath) override;

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	virtual void update(float dt);

protected:
	virtual void setControllerInBgLayer() override;

	void addPlayer(experimental::TMXTiledMap* tiledMap);	// ������

	void firstEnterGame();	// ��һ�ν�����Ϸ

	void onEnter() override;

	void loadMapResurce(); // �����ͼ��Դ

	/* ͼƬ���ػص����� */
	void imageLoadCallFunc(Texture2D* texture);

private:
	Player* m_player;	// ��Ҷ���

	TollgateLogicLayer* m_logicLayer; // �߼���
	TollgatBgLayer* m_bgLayer;		 // ������
	TollgateMapLayer* m_mapLayer;    // ��ͼ��
	TollgateSplashLayer* m_spalshLayer;  // ���ɲ�

	int m_curLevel;		// ��ǰ�ؿ�

	int m_loadResCnt;	// ������Դ����
};

#endif // !__TOLLGATE_SCENE_H__
