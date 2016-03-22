#pragma once
#ifndef _ENTITY_H__
#define _ENTITY_H__

#include "cocos2d.h"

USING_NS_CC;


/******************************************************* 实体基类 ******************************************************/

class BaseEntity : public Node
{
public:
	virtual bool init();

protected:
	CC_SYNTHESIZE(int, m_id, Id);							// 实体id
	CC_SYNTHESIZE(int, m_modelId, ModelId);					// 模型id
	CC_SYNTHESIZE(std::string, m_entityName, EntityName);	// 实体名
	CC_SYNTHESIZE(std::string, m_lifeValue, LifeValue);		// 实体生命值
	CC_SYNTHESIZE(std::string, m_speed, Speed);				// 实体速度
	CC_SYNTHESIZE(std::string, m_level, Level);				// 实体级别
	CC_SYNTHESIZE(std::string, m_defense, Defense);			// 实体防御力
};

#endif // !_ENTITY_H__
