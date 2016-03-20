#include "StringUtil.h"

StringUtil* StringUtil::m_StringUtil = nullptr;

StringUtil * StringUtil::getInstance()
{
	if (!m_StringUtil)
	{
		m_StringUtil = new StringUtil();
		if (m_StringUtil && m_StringUtil->init())
		{
			m_StringUtil->autorelease();
			m_StringUtil->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_StringUtil);
			m_StringUtil = nullptr;
		}
	}

	return m_StringUtil;
}

bool StringUtil::init()
{
	return true;
}

ValueVector StringUtil::split(const char * srcStr, const char * sSep)
{
	ValueVector stringList;

	int size = strlen(srcStr);

	/* 将数据转换为Value对象 */
	Value str = Value(srcStr);

	int startIndex = 0;
	int endIndex = 0;

	endIndex = str.asString().find(sSep);

	std::string lineStr = "";
	/* 根据换行符拆分字符串，并添加到列表 */
	while (endIndex > 0)
	{
		lineStr = str.asString().substr(startIndex, endIndex);
		stringList.push_back(Value(lineStr));
		str = Value(str.asString().substr(endIndex + 1, size));

		endIndex = str.asString().find(sSep);
	}

	/* 剩余字符串添加进列表 */
	if (str.asString().compare("") != 0)
	{
		stringList.push_back(Value(str.asString()));
	}

	return stringList;
}
