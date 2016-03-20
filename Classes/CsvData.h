#pragma once
#ifndef __CSV_DATA_H__
#define __CSV_DATA_H__

#include "cocos2d.h"

USING_NS_CC;


/*********************************** csv������ **************************************/

class CsvData : public Ref
{
public:
	CREATE_FUNC(CsvData);

	virtual bool init();

	void addLineData(ValueVector lineData);		/*���һ������ */
	ValueVector getSingleLineData(int iLine);	/*��õ������� */
	Size getRowColNum();						/* ��ȡ���д�С */

private:
	/* ���csv�ļ����������� */
	ValueVector m_allLinesVec;

	/* ���� */
	int m_iColNum;

};
#endif // !__CSV_DATA_H__
