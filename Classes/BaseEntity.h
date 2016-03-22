#pragma once
#ifndef _ENTITY_H__
#define _ENTITY_H__

#include "cocos2d.h"

USING_NS_CC;


/******************************************************* ʵ����� ******************************************************/

class BaseEntity : public Node
{
public:
	virtual bool init();

protected:
	CC_SYNTHESIZE(int, m_id, Id);							// ʵ��id
	CC_SYNTHESIZE(int, m_modelId, ModelId);					// ģ��id
	CC_SYNTHESIZE(std::string, m_entityName, EntityName);	// ʵ����
	CC_SYNTHESIZE(std::string, m_lifeValue, LifeValue);		// ʵ������ֵ
	CC_SYNTHESIZE(std::string, m_speed, Speed);				// ʵ���ٶ�
	CC_SYNTHESIZE(std::string, m_level, Level);				// ʵ�弶��
	CC_SYNTHESIZE(std::string, m_defense, Defense);			// ʵ�������
};

#endif // !_ENTITY_H__
