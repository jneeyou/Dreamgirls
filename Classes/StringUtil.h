#pragma once
#ifndef __STRING_UTIL_H__
#define __STRING_UTIL_H__

#include "cocos2d.h"

using namespace cocos2d;

/************************************** 字符串工具类 ***************************************************/

class StringUtil : public Ref
{
public:
	static StringUtil* getInstance();

	virtual bool init();

	/* 用分隔符分割字符串，结果存于Vector中，列表中对象为Value */
	ValueVector split(const char* srcStr, const char* sSep);

private:
	static StringUtil* m_StringUtil;
};

#endif // !__STRING_UTIL_H__
