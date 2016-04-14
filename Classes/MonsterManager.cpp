#include "MonsterManager.h"
#include "Player.h"

MonsterManager* MonsterManager::m_monsterManager = nullptr;

bool MonsterManager::init()
{
	//createMonsters();		/* �������ﻺ�� */
	//this->scheduleUpdate(); /* ����update�������� */

	return true;
}

void MonsterManager::update(float dt)
{
	//for (auto monster : m_monsterArr)
	//{
	//	if (monster->isAlive())
	//	{
	//		/* ������ﴦ�ڻ״̬ */
	//		monster->setPositionX(monster->getPositionX() - 4);

	//		/* �������x���곬����Ļ�����ع��� */
	//		if (monster->getPositionX() < 0)
	//		{
	//			monster->hide();
	//		}
	//		/* �жϹ����Ƿ���ײ��� */
	//		else if (monster->isCollideWithPlayer(m_player))
	//		{
	//			m_player->hit();
	//			monster->hide();


	//		}
	//	}
	//	else
	//	{
	//		/* ������ﴦ�ڷǻ�����ù������ */
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
		/* ����������� */
		monster =  Monster::createMonsterByPosAndName(pos, name); 

		/* ��ӹ������ */
		this->addChild(monster);

		/* �����������б� */
		m_monsterArr.pushBack(monster);
	}

	return monster;
}