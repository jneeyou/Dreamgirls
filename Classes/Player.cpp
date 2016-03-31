#include "Player.h"
#include "CsvUtil.h"

/* 动画名 */
#define RUN_ANIMATION_NAME		"run"
#define JUMP_ANIMATION_NAME		"jump"
#define CATCH_ANIMATION_NAME	"catch"

Player::Player()
{
	m_curWalkDistance = 0;
}

Player::~Player()
{
	if (m_timeline)
	{
		m_timeline->release();
	}

}

bool Player::init(const char * csvFilePath)
{
	if (!BaseEntity::init())
	{
		return false;
	}

	/* 通过配置文件设置属性 */
	setPlayerProperties(csvFilePath);

	/* 获取动画 */
	loadPlayerAnimation(PATH_PLAYER_AIMATION_FILE);


	return true;
}

void Player::run()
{
	if (m_sprite != nullptr)
	{
		if (m_timeline->IsAnimationInfoExists(RUN_ANIMATION_NAME))
		{
			m_timeline->play(RUN_ANIMATION_NAME, true);	// 播放跑动画
			m_sprite->runAction(m_timeline);
		}
	}
}

void Player::onWalk()
{
}

void Player::onJump()
{
	if (m_entityStatus == BaseEntity::EntityStatus::en_Jump_Status)
	{
		return;
	}

	stopAllActions();
}

void Player::onCatch()
{
}

void Player::onAttack()
{
}

void Player::onIncreateLife(int lifeValue)
{
}

void Player::onGetTool()
{
}

void Player::onUseTool()
{
}

void Player::loadPlayerAnimation(const std::string fileName)
{
	m_timeline = CSLoader::createTimeline(fileName);
	m_timeline->retain();

}

void Player::setPlayerProperties(const char* csvFilePath)
{
	m_id = CsvUtil::getInstance()->getInt(1, 1, csvFilePath);
	m_modelId = CsvUtil::getInstance()->getInt(1, 2, csvFilePath);
	m_entityName = CsvUtil::getInstance()->getString(1, 3, csvFilePath);
	m_level = CsvUtil::getInstance()->getInt(1, 4, csvFilePath);
	m_lifeValue = CsvUtil::getInstance()->getInt(1, 5, csvFilePath);
	m_speed = CsvUtil::getInstance()->getFloat(1, 6, csvFilePath);
	m_defense = CsvUtil::getInstance()->getFloat(1, 7, csvFilePath);
	m_curAct = CsvUtil::getInstance()->getInt(1, 8, csvFilePath);
}
