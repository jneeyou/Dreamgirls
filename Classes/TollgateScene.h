#pragma once
#ifndef __TOLLGATE_SCENE_H__
#define __TOLLGATE_SCENE_H__

#include "BaseScene.h"

class Player;

/*************************************************** �ؿ����� *******************************************/

class TollgateScene : public BaseScene
{
public:
	CREATE_FUNC_0(TollgateScene, const char);
	CREATE_SCENE_0(TollgateScene, const char);

	virtual bool init(const char* filePath) override;

protected:
	virtual void setControllerInBgLayer() override;

	void addPlayer(TMXTiledMap* tiledMap);	// ������

	void moveBg(float dt);	// �ƶ�����

private:
	TextBMFont* m_scoreLabel;	// �������

	Player* m_player;	// ��Ҷ���

	Sprite* m_bottomBg;
	Sprite* m_topBg;
};

#endif // !__TOLLGATE_SCENE_H__
