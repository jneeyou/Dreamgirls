#pragma once
#ifndef __CSV_UTIL_H__
#define __CSV_UTIL_H__

#include "cocos2d.h"

USING_NS_CC;

class CsvData;

/******************************** csv读取工具类 ***********************************/

class CsvUtil : public Ref
{
public:
	virtual bool init();

	static CsvUtil* getInstance();

	void loadFile(const char* filePath);	/* 加载配置文件 */

	Value getValue(int iRow, int iCol, const char* csvFilePath);				/* 获取某行某列的值 */
	const std::string getString(int iRow, int iCol, const char* csvFilePath);	/* 获取值并转换为字符串 */
	const int getInt(int iRow, int iCol, const char* csvFilePath);				/* 获取值并转换为整型值 */
	const float getFloat(int iRow, int iCol, const char* csvFilePath);			/* 获取值并转换为float值 */
	const bool getBool(int iRow, int iCol, const char* csvFilePath);			/* 获取值并转换为bool值 */
	const double getDouble(int iRow, int iCol, const char* csvFilePath);		/* 获取值并转换为double值 */
	const char getByte(int iRow, int iCol, const char* csvFilePath);			/* 获取值并转换为Byte值 */

	const Size getFileRowColNum(const char* csvFilePath);						/* 获取csv文件行列数 */	

	/* 根据某列的值查找该值所在行 */
	const int findValueInWithLine(const char* chValue, int iValueCol, const char* csvFilePath);

private:
	static CsvUtil* m_CsvUtil;
	Map<std::string, CsvData*> m_CsvMap;	/* 存放csv字符串列表和csv文件路径映射关系 */
};
#endif // !__CSV_UTIL_H__
