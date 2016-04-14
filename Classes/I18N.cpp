#include "I18N.h"
#include "GlobalDefine.h"
#include "CsvUtil.h"

I18N* I18N::m_I18N = nullptr;

I18N * I18N::getInstance()
{
	if (!m_I18N)
	{
		m_I18N = new I18N();
		if (m_I18N && m_I18N->init())
		{
			m_I18N->autorelease();
			m_I18N->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_I18N);
		}
	}

	return m_I18N;
}

bool I18N::init()
{
	/* 读取配置文件 */
	loadStringsFromConf(PATH_I18N_PUBLIC);

	return true;
}

const char * I18N::getcString(EnumStrKey enStrKey)
{
	log("here");

	if (enStrKey > m_StringMap.size())
	{
		return "";
	}
	return m_StringMap.at(enStrKey).c_str();
}

const char * I18N::getcStringByKey(int iKey)
{
	if (iKey > m_StringMap.size())
	{
		return "";
	}
	return m_StringMap.at(iKey).c_str();
}

const std::string I18N::getsString(EnumStrKey enStrKey)
{
	if (enStrKey > m_StringMap.size())
	{
		return "";
	}
	return m_StringMap.at(enStrKey);
}

const std::string I18N::getsStringByKey(int iKey)
{
	if (iKey > m_StringMap.size())
	{
		return "";
	}
	return m_StringMap.at(iKey);
}


void I18N::loadStringsFromConf(const char * filePath)
{
	CsvUtil::getInstance()->loadFile(filePath);

	Size size = CsvUtil::getInstance()->getFileRowColNum(filePath);

	int iRowNum = size.width;
	int iColNum = size.height;

	/* 如果列数小于2，表示配置文件有问题 */
	if (iColNum < 2)
	{
		return;
	}

	/* 将配置文件中所有字符串存到字典中（忽略第一行）*/
	for (int i = 1; i < iRowNum; i++)
	{
		int key = CsvUtil::getInstance()->getInt(i, 1, filePath);
		std::string value = CsvUtil::getInstance()->getString(i, 2, filePath);
		log("data:%s", value.c_str());
		m_StringMap[key] = value;
	}
}
