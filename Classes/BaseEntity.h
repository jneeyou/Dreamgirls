#pragma once
#ifndef _ENTITY_H__
#define _ENTITY_H__

#include "cocos2d.h"

USING_NS_CC;

/******************************************************* ʵ����� ******************************************************/

class BaseEntity : public Node
{
public:
	/* ʵ��״̬���� */
	enum class EntityStatus 
	{
		en_Live_Status,		// �״̬
		en_Sleep_Status,	// ����״̬
		en_Dead_Status,		// ����״̬

	};	// EntityStatus

public:
	virtual bool init();

	/* ʵ�屻�������� */
	 void AttackedHurt(int hurtValue);

	/* ��þ��� */
	Sprite* getSprite();

	/* �󶨾��� */
	void bindSprite();

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
	CC_SYNTHESIZE(int, m_id, Id);							 // ʵ��id
	CC_SYNTHESIZE(int, m_modelId, ModelId);					 // ģ��id
	CC_SYNTHESIZE(std::string, m_entityName, EntityName);	 // ʵ����
	CC_SYNTHESIZE(std::string, m_lifeValue, LifeValue);		 // ʵ������ֵ
	CC_SYNTHESIZE(std::string, m_speed, Speed);				 // ʵ���ٶ�
	CC_SYNTHESIZE(std::string, m_level, Level);				 // ʵ�弶��
	CC_SYNTHESIZE(std::string, m_defense, Defense);			 // ʵ�������

	CC_SYNTHESIZE(EntityStatus, m_entityStatus, EntiyStatus); // ʵ��״̬

private:
	Sprite* m_sprite;	// ʵ����־���
};

#endif // !_ENTITY_H__
