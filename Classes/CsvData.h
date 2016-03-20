#pragma once
#ifndef __CSV_DATA_H__
#define __CSV_DATA_H__

#include "cocos2d.h"

USING_NS_CC;


/*********************************** csv数据类 **************************************/

class CsvData : public Ref
{
public:
	CREATE_FUNC(CsvData);

	virtual bool init();

	void addLineData(ValueVector lineData);		/*添加一行数据 */
	ValueVector getSingleLineData(int iLine);	/*获得单行数据 */
	Size getRowColNum();						/* 获取行列大小 */

private:
	/* 存放csv文件所有行数据 */
	ValueVector m_allLinesVec;

	/* 列数 */
	int m_iColNum;

};
#endif // !__CSV_DATA_H__
