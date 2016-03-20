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
};

#endif // !_ENTITY_H__
