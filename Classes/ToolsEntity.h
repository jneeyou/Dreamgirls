#pragma once
#ifndef __TOO_LENTITY_H__
#define __TOO_LENTITY_H__

#include "BaseEntity.h"
#include "GlobalDefine.h"

/*********************************************** ����ʵ���� ************************************************/

class ToolEntity : public BaseEntity
{
public:
	ToolEntity();
	~ToolEntity();

	/* ͨ��csv�����ļ����� */
	CREATE_FUNC_0(ToolEntity, const char);
	virtual bool init(const char* csvFilePath);
};

#endif // !__TOO_LENTITY_H__
