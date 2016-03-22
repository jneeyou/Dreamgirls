#pragma once
#ifndef _ENTITY_H__
#define _ENTITY_H__

#include "cocos2d.h"

USING_NS_CC;

/******************************************************* 实体基类 ******************************************************/

class BaseEntity : public Node
{
public:
	/* 实体状态类型 */
	enum class EntityStatus 
	{
		en_Live_Status,		// 活动状态
		en_Sleep_Status,	// 休眠状态
		en_Dead_Status,		// 死亡状态

	};	// EntityStatus

public:
	virtual bool init();

	/* 实体被攻击受伤 */
	 void AttackedHurt(int hurtValue);

	/* 获得精灵 */
	Sprite* getSprite();

	/* 绑定精灵 */
	void bindSprite();

protected:
	/* 移动位置 */
	virtual void movePos();

	/* 绑定精灵 */
	virtual void onBindSprite();

	/* 实体死亡 */
	virtual void onDead();

	/* 实体受伤 */
	virtual void onHurt(int hurtValue);

protected:
	CC_SYNTHESIZE(int, m_id, Id);							 // 实体id
	CC_SYNTHESIZE(int, m_modelId, ModelId);					 // 模型id
	CC_SYNTHESIZE(std::string, m_entityName, EntityName);	 // 实体名
	CC_SYNTHESIZE(std::string, m_lifeValue, LifeValue);		 // 实体生命值
	CC_SYNTHESIZE(std::string, m_speed, Speed);				 // 实体速度
	CC_SYNTHESIZE(std::string, m_level, Level);				 // 实体级别
	CC_SYNTHESIZE(std::string, m_defense, Defense);			 // 实体防御力

	CC_SYNTHESIZE(EntityStatus, m_entityStatus, EntiyStatus); // 实体状态

private:
	Sprite* m_sprite;	// 实体表现精灵
};

#endif // !_ENTITY_H__
