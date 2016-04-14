#include "MonsterManager.h"
#include "Player.h"

MonsterManager* MonsterManager::m_monsterManager = nullptr;

bool MonsterManager::init()
{
	//createMonsters();		/* 创建怪物缓存 */
	//this->scheduleUpdate(); /* 开启update函数调用 */

	return true;
}

void MonsterManager::update(float dt)
{
	//for (auto monster : m_monsterArr)
	//{
	//	if (monster->isAlive())
	//	{
	//		/* 如果怪物处于活动状态 */
	//		monster->setPositionX(monster->getPositionX() - 4);

	//		/* 如果怪物x坐标超出屏幕，隐藏怪物 */
	//		if (monster->getPositionX() < 0)
	//		{
	//			monster->hide();
	//		}
	//		/* 判断怪物是否碰撞玩家 */
	//		else if (monster->isCollideWithPlayer(m_player))
	//		{
	//			m_player->hit();
	//			monster->hide();


	//		}
	//	}
	//	else
	//	{
	//		/* 如果怪物处于非活动，让让怪物出场 */
	//		monster->show();
	//	}
	//}
}

void MonsterManager::bindPlayer(Player * player)
{
	m_player = player;
}

Monster* MonsterManager::createMonsterByPosAndName(Vec2& pos, std::string& name)
{
	Monster* monster = nullptr;


	for (int i = 0; i < MAX_MONSTER_NUM; i++)
	{
		/* 创建怪物对象 */
		monster =  Monster::createMonsterByPosAndName(pos, name); 

		/* 添加怪物对象 */
		this->addChild(monster);

		/* 保存怪物对象到列表 */
		m_monsterArr.pushBack(monster);
	}

	return monster;
}