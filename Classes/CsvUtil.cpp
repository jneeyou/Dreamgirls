#include "CsvUtil.h"
#include "CsvData.h"
#include "StringUtil.h"

CsvUtil* CsvUtil::m_CsvUtil = nullptr;

#define NOT_FIND	-1

bool CsvUtil::init()
{
	return true;
}

CsvUtil * CsvUtil::getInstance()
{
	if (!m_CsvUtil)
	{
		m_CsvUtil = new CsvUtil();

		if (m_CsvUtil && m_CsvUtil->init())
		{
			m_CsvUtil->autorelease();
			m_CsvUtil->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_CsvUtil);
			m_CsvUtil = nullptr;
		}
	}

	return m_CsvUtil;
}

void CsvUtil::loadFile(const char * filePath)
{
	/* ���һ��csv�ļ��Ķ��� */
	CsvData* csvData = CsvData::create();

	/* ��ȡ���ݣ����б��浽�б� */
	std::string str = FileUtils::getInstance()->getStringFromFile(filePath);
	ValueVector linesList = StringUtil::getInstance()->split(str.c_str(), "\n");

	/* ��ÿһ�����ݲ�ֳ���,������Ϊһ����ά��� */
	for (auto value : linesList)
	{
		ValueVector lineArr = StringUtil::getInstance()->split(value.asString().c_str(), ",");
		csvData->addLineData(lineArr);
	}

	/* ����б��ֵ��� */
	m_CsvMap.insert(filePath, csvData);
}

Value CsvUtil::getValue(int iRow, int iCol, const char * csvFilePath)
{
	/* ȡ��csv�ļ����� */
	auto csvData = m_CsvMap.at(csvFilePath);

	if (!csvData)
	{
		loadFile(csvFilePath);
		csvData = m_CsvMap.at(csvFilePath);
	}

	ValueVector rowVector = csvData->getSingleLineData(iRow);	/* ȡ��iRow������ */
	if (rowVector.size() == 0)	/* ȡ��iCo������ */
	{
		return Value("");
	}

	Value colValue = rowVector.at(iCol);

	return colValue;
}

const std::string CsvUtil::getString(int iRow, int iCol, const char * csvFilePath)
{
	Value colValue = getValue(iRow, iCol, csvFilePath);

	return colValue.asString();
}

const int CsvUtil::getInt(int iRow, int iCol, const char * csvFilePath)
{
	Value colValue = getValue(iRow, iCol, csvFilePath);

	return colValue.asInt();
}

const float CsvUtil::getFloat(int iRow, int iCol, const char * csvFilePath)
{
	Value colValue = getValue(iRow, iCol, csvFilePath);

	return colValue.asFloat();
}

const bool CsvUtil::getBool(int iRow, int iCol, const char * csvFilePath)
{
	Value colValue = getValue(iRow, iCol, csvFilePath);

	return colValue.asBool();
}

const double CsvUtil::getDouble(int iRow, int iCol, const char * csvFilePath)
{
	Value colValue = getValue(iRow, iCol, csvFilePath);

	return colValue.asDouble();
}

const char CsvUtil::getByte(int iRow, int iCol, const char * csvFilePath)
{
	Value colValue = getValue(iRow, iCol, csvFilePath);

	return colValue.asByte();
}

const Size CsvUtil::getFileRowColNum(const char * csvFilePath)
{
	/* ȡ�������ļ��Ķ�ά��� */
	auto csvData = m_CsvMap.at(csvFilePath);

	/* ��������ļ����ݲ����ڣ����������ļ� */
	if (csvData == nullptr)
	{
		loadFile(csvFilePath);
		csvData = m_CsvMap.at(csvFilePath);
	}

	Size size = csvData->getRowColNum();

	return size;
}

/**
 ����NOT_FINDδ�ҵ�
**/
const int CsvUtil::findValueInWithLine(const char * chValue, int iValueCol, const char * csvFilePath)
{
	/* ȡ�������ļ��Ķ�ά��� */
	auto csvData = m_CsvMap.at(csvFilePath);

	/* ��������ļ����ݲ����ڣ����������ļ� */
	if (csvData == nullptr)
	{
		loadFile(csvFilePath);
		csvData = m_CsvMap.at(csvFilePath);
	}

	Size rowColNum = csvData->getRowColNum();
	for (size_t i = 0; i < rowColNum.width; i++)
	{
		if (!csvData->getSingleLineData(i).at(iValueCol).asString().compare(chValue))
		{
			return i;
		}
	}

	return NOT_FIND;
}
