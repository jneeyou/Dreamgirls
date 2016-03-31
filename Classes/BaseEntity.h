#pragma once
#ifndef _ENTITY_H__
#define _ENTITY_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

using namespace cocostudio::timeline;

/******************************************************* ʵ����� ******************************************************/

class BaseEntity : public Node
{
public:
	/* ʵ��״̬���� */
	enum class EntityStatus 
	{
		en_Walk_Status,		// �߶�״̬
		en_Attack_Status,	// ����״̬
		en_BeAttack_Status,	// ������״̬
		en_Jump_Status,		// ��Ծ״̬
		en_Run_Status,		// �ܶ�״̬
		en_Restore_Status,	// �ָ�״̬
		en_Fly_Status,		// ����״̬
		en_Boat_Status,		// ����״̬
		en_Sleep_Status,	// ����״̬
		en_Dead_Status,		// ����״̬

	};	// EntityStatus

public:
	BaseEntity();
	~BaseEntity();

	virtual bool init();

	/* ʵ�屻�������� */
	 void AttackedHurt(int hurtValue);

	/* ��þ��� */
	 SkeletonNode* getSprite();

	/* �󶨾��� */
	void bindSprite(SkeletonNode* sprite);

protected:
	/* �ƶ�λ�� */
	virtual void movePos();

	/* �󶨾��� */
	virtual void onBindSprite();

	/* ʵ������ */
	virtual void onDead();

	/* ʵ������ */
	virtual void onHurt(int hurtValue);

protected:
	CC_SYNTHESIZE(int, m_id, Id);								// ʵ��id
	CC_SYNTHESIZE(int, m_modelId, ModelId);						// ģ��id
	CC_SYNTHESIZE(std::string, m_entityName, EntityName);		// ʵ����
	CC_SYNTHESIZE(int, m_lifeValue, LifeValue);					// ʵ������ֵ
	CC_SYNTHESIZE(float, m_speed, Speed);						// ʵ���ٶ�
	CC_SYNTHESIZE(int, m_level, Level);							// ʵ�弶��
	CC_SYNTHESIZE(float, m_defense, Defense);					// ʵ�������


	EntityStatus m_entityStatus;	// ʵ��״̬

	/* �ı�״̬ */
	void setEntityStatus(EntityStatus status);
	EntityStatus getEntityStatus();

protected:
	SkeletonNode* m_sprite;	// ʵ����־���
};

#endif // !_ENTITY_H__
