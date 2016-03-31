#pragma once
#ifndef _ENTITY_H__
#define _ENTITY_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

using namespace cocostudio::timeline;

/******************************************************* 实体基类 ******************************************************/

class BaseEntity : public Node
{
public:
	/* 实体状态类型 */
	enum class EntityStatus 
	{
		en_Walk_Status,		// 走动状态
		en_Attack_Status,	// 攻击状态
		en_BeAttack_Status,	// 被攻击状态
		en_Jump_Status,		// 跳跃状态
		en_Run_Status,		// 跑动状态
		en_Restore_Status,	// 恢复状态
		en_Fly_Status,		// 飞行状态
		en_Boat_Status,		// 坐船状态
		en_Sleep_Status,	// 休眠状态
		en_Dead_Status,		// 死亡状态

	};	// EntityStatus

public:
	BaseEntity();
	~BaseEntity();

	virtual bool init();

	/* 实体被攻击受伤 */
	 void AttackedHurt(int hurtValue);

	/* 获得精灵 */
	 SkeletonNode* getSprite();

	/* 绑定精灵 */
	void bindSprite(SkeletonNode* sprite);

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
	CC_SYNTHESIZE(int, m_id, Id);								// 实体id
	CC_SYNTHESIZE(int, m_modelId, ModelId);						// 模型id
	CC_SYNTHESIZE(std::string, m_entityName, EntityName);		// 实体名
	CC_SYNTHESIZE(int, m_lifeValue, LifeValue);					// 实体生命值
	CC_SYNTHESIZE(float, m_speed, Speed);						// 实体速度
	CC_SYNTHESIZE(int, m_level, Level);							// 实体级别
	CC_SYNTHESIZE(float, m_defense, Defense);					// 实体防御力


	EntityStatus m_entityStatus;	// 实体状态

	/* 改变状态 */
	void setEntityStatus(EntityStatus status);
	EntityStatus getEntityStatus();

protected:
	SkeletonNode* m_sprite;	// 实体表现精灵
};

#endif // !_ENTITY_H__
