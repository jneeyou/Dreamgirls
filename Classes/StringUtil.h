#pragma once
#ifndef __STRING_UTIL_H__
#define __STRING_UTIL_H__

#include "cocos2d.h"

using namespace cocos2d;

/************************************** �ַ��������� ***************************************************/

class StringUtil : public Ref
{
public:
	static StringUtil* getInstance();

	virtual bool init();

	/* �÷ָ����ָ��ַ������������Vector�У��б��ж���ΪValue */
	ValueVector split(const char* srcStr, const char* sSep);

private:
	static StringUtil* m_StringUtil;
};

#endif // !__STRING_UTIL_H__
