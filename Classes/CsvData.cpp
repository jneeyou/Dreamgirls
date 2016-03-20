#include "CsvData.h"

bool CsvData::init()
{
	m_iColNum = 0;
	return true;
}

void CsvData::addLineData(ValueVector lineData)
{
	m_allLinesVec.push_back(Value(lineData));

	m_iColNum = m_iColNum >= lineData.size() ? m_iColNum : lineData.size();
}

ValueVector CsvData::getSingleLineData(int iLine)
{
	if (iLine < 0 || iLine > m_allLinesVec.size())
	{
		return ValueVector();
	}

	return m_allLinesVec.at(iLine).asValueVector();
}

Size CsvData::getRowColNum()
{
	Size size = Size();

	size.width = m_allLinesVec.size();
	if (size.width > 0)
	{
		size.height = m_iColNum;
	}

	return size;
}
