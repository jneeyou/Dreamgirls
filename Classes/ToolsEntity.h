#pragma once
#ifndef __TOO_LENTITY_H__
#define __TOO_LENTITY_H__

#include "BaseEntity.h"
#include "GlobalDefine.h"

/*********************************************** 道具实体类 ************************************************/

class ToolEntity : public BaseEntity
{
public:
	ToolEntity();
	~ToolEntity();

	/* 通过csv配置文件创建 */
	CREATE_FUNC_0(ToolEntity, const char);
	virtual bool init(const char* csvFilePath);
};

#endif // !__TOO_LENTITY_H__
