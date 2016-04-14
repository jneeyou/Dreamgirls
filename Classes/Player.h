#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "BaseEntity.h"
#include "GlobalDefine.h"
#include "cocostudio\CocoStudio.h"

using namespace cocostudio::timeline;

typedef experimental::TMXTiledMap ETMXTileMap;
typedef experimental::TMXLayer ETMXLayer;

/************************************************* ����� **********************************************/

class Player : public BaseEntity
{
public:
	Player();
	~Player();

	/* ͨ��csv�����ļ����� */
	CREATE_FUNC_0(Player, const char);

	virtual bool init(const char* csvFilePath);

	/* �� */
	void run(bool isLeft);

	/*ֹͣ�� */
	void stopRun();

	/* �� */
	void jump(int high);

	/* ����������ͼλ�� */
	void setViewPointByPlayer();

	/* ����Ŀ��λ�� */
	virtual void setTagPosition(int x, int y);

	/* ���õ�ͼ */
	void setTiedMap(experimental::TMXTiledMap* map);

	void update(float dt);

protected:
	/* �� */
	void onWalk();

	/* ץ */
	void onCatch ();

	/* ���� */
	void onAttack();

	/* �������� */
	void onIncreateLife(int lifeValue);

	/* ��õ��� */
	void onGetTool();

	/* ʹ�õ��� */
	void onUseTool();

	/* �󶨾��� */
	virtual void onBindSprite() override;

protected:
	/* ������Ҷ��� */
	void loadPlayerAnimation(const std::string fileName);

	/* ����������� */
	void setPlayerProperties(int iRow,const char* csvFilePath);

	/* �ƶ�λ�� */
	void movePos(float dt, float dis);

	/* ����������ת��Ϊ��ͼ�������� */
	Point tileCoordForPosition(Point pos);

	CC_SYNTHESIZE(int, m_curAct, CurAct);						// ��ǰ������
	CC_SYNTHESIZE(int, m_curWalkDistance, CurWalkDistance);		// ���߾���

	/* �����Ƿ����� */
	void setIsLeftMove(bool isLeft);

private:
	/* ʱ���߶��� */
	ActionTimeline* m_timeline;

	/* �Ƿ����� */
	bool m_isLeftMove;

	/* �Ƿ�ص� */
	bool m_isRebound;

	/* ��ͼ */
	experimental::TMXTiledMap* m_map;

	/* ��ײ���� */
	experimental::TMXLayer* m_metaLayer;
		
	/* �ܶ�ʱ�� */
	float runTime;

	/* ��Ծʱ�� */
	float jumpTime;

	/* �Ƿ����� */
	bool m_isRunning;

};

#endif // !__PLAYER_H__
