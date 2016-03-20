#pragma once
#ifndef __CSV_UTIL_H__
#define __CSV_UTIL_H__

#include "cocos2d.h"

USING_NS_CC;

class CsvData;

/******************************** csv��ȡ������ ***********************************/

class CsvUtil : public Ref
{
public:
	virtual bool init();

	static CsvUtil* getInstance();

	void loadFile(const char* filePath);	/* ���������ļ� */

	Value getValue(int iRor, int iCol, const char* csvFilePath);				/* ��ȡĳ��ĳ�е�ֵ */
	const std::string getString(int iRor, int iCol, const char* csvFilePath);	/* ��ȡֵ��ת��Ϊ�ַ��� */
	const int getInt(int iRor, int iCol, const char* csvFilePath);				/* ��ȡֵ��ת��Ϊ����ֵ */
	const float getFloat(int iRor, int iCol, const char* csvFilePath);			/* ��ȡֵ��ת��Ϊfloatֵ */
	const bool getBool(int iRor, int iCol, const char* csvFilePath);			/* ��ȡֵ��ת��Ϊboolֵ */
	const double getDouble(int iRor, int iCol, const char* csvFilePath);		/* ��ȡֵ��ת��Ϊdoubleֵ */
	const char getByte(int iRor, int iCol, const char* csvFilePath);			/* ��ȡֵ��ת��ΪByteֵ */

	const Size getFileRowColNum(const char* csvFilePath);						/* ��ȡcsv�ļ������� */	

	/* ����ĳ�е�ֵ���Ҹ�ֵ������ */
	const int findValueInWithLine(const char* chValue, int iValueCol, const char* csvFilePath);

private:
	static CsvUtil* m_CsvUtil;
	Map<std::string, CsvData*> m_CsvMap;	/* ���csv�ַ����б��csv�ļ�·��ӳ���ϵ */
};
#endif // !__CSV_UTIL_H__
