#pragma once
#ifndef __I_18_N_H__
#define __I_18_N_H__

#include "EnumStrKey.h"
#include "cocos2d.h"

USING_NS_CC;

class I18N : public Ref
{
public:
	static I18N* getInstance();

	virtual bool init();

	/* 根据key值获取字符串，返回const char* 对象 */
	const char* getcString(EnumStrKey enStrKey);

	/* 根据整型key值获取字符串，返回const char* 对象 */
	const char* getcStringByKey(int iKey);

	/* 根据key值获取字符串，返回const string 对象 */
	const std::string getsString(EnumStrKey enStrKey);

	/* 根据整型key值获取字符串，返回const string 对象 */
	const std::string getsStringByKey(int iKey);

private:
	/* 从配置文件中读取字符串，保存到字典里 */
	void loadStringsFromConf(const char* filePath);

	/* I18N对象 */
	static I18N* m_I18N;

	/* 游戏中用到的字符串字典 */
	std::map<int, std::string> m_StringMap;
};

#endif // !__I_18_N_H__
