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

	/* ����keyֵ��ȡ�ַ���������const char* ���� */
	const char* getcString(EnumStrKey enStrKey);

	/* ��������keyֵ��ȡ�ַ���������const char* ���� */
	const char* getcStringByKey(int iKey);

	/* ����keyֵ��ȡ�ַ���������const string ���� */
	const std::string getsString(EnumStrKey enStrKey);

	/* ��������keyֵ��ȡ�ַ���������const string ���� */
	const std::string getsStringByKey(int iKey);

private:
	/* �������ļ��ж�ȡ�ַ��������浽�ֵ��� */
	void loadStringsFromConf(const char* filePath);

	/* I18N���� */
	static I18N* m_I18N;

	/* ��Ϸ���õ����ַ����ֵ� */
	std::map<int, std::string> m_StringMap;
};

#endif // !__I_18_N_H__
