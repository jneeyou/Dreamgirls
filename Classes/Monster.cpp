#include "Monster.h"
#include "CsvUtil.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

bool Monster::init()
{
	return true;
}

bool Monster::init(const char * csvFilePath)
{
	return true;
}

bool Monster::isCollide(BaseEntity * player)
{

	return false;
}

Monster* Monster::createMonsterByPosAndName(Vec2 & pos, std::string & name)
{
	auto monster = Monster::create();
	monster->setPosition(pos);

	// 通过名字获取属性

	// 获得属性行号
	int row = CsvUtil::getInstance()->findValueInWithLine(name.c_str(), 3, PATH_CSV_MONSTER);

	//获得该行所有属性
	monster->setMonsterProperties(row, PATH_CSV_MONSTER);

	return monster;
}

void Monster::setMonsterProperties(int iRow, const char * csvFilePath)
{
	m_id = CsvUtil::getInstance()->getInt(iRow, 1, csvFilePath);
	m_modelId = CsvUtil::getInstance()->getInt(iRow, 2, csvFilePath);
	m_entityName = CsvUtil::getInstance()->getString(iRow, 3, csvFilePath);
	m_level = CsvUtil::getInstance()->getInt(iRow, 4, csvFilePath);
	m_lifeValue = CsvUtil::getInstance()->getInt(iRow, 5, csvFilePath);
	m_speed = CsvUtil::getInstance()->getFloat(iRow, 6, csvFilePath);
	m_defense = CsvUtil::getInstance()->getFloat(iRow, 7, csvFilePath);
	m_monsterAck = CsvUtil::getInstance()->getInt(iRow, 8, csvFilePath);
}
