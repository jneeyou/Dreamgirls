#include "Player.h"
#include "CsvUtil.h"
#include "SceneManager.h"
#include "GlobalDefine.h"

/* ������ */
#define RUN_ANIMATION_NAME		"run"
#define JUMP_ANIMATION_NAME		"jump"
#define CATCH_ANIMATION_NAME	"catch"

/* ��ͼ�� */
#define META_LAYER	"road"

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

	m_isRebound = false;
	runTime = 0;
	jumpTime = 0;
	m_isRunning = false;

	/* ͨ�������ļ��������� */
	setPlayerProperties(1,csvFilePath);

	/* ��ȡ���� */
	loadPlayerAnimation(PATH_PLAYER_AIMATION_FILE);

	return true;
}

void Player::run(bool isLeft)
{
	if (m_entityStatus == BaseEntity::EntityStatus::en_Jump_Status
		|| m_entityStatus == BaseEntity::EntityStatus::en_Run_Status)
	{
		return;
	}

	/* ���÷��� */
	setIsLeftMove(isLeft);

	/* ֹͣ���ж��� */
	this->stopAllActions();
	m_timeline->gotoFrameAndPause(0);

	if (m_sprite != nullptr)
	{
		if (m_timeline->IsAnimationInfoExists(RUN_ANIMATION_NAME))
		{
			m_timeline->play(RUN_ANIMATION_NAME, true);	// �����ܶ���
		}
	}

	/* �ƶ�λ�� */
	movePos(runTime, m_speed);
	m_isRunning = true;
	m_entityStatus = BaseEntity::EntityStatus::en_Run_Status;

	this->scheduleUpdate();
	NOTIFY->postNotification(TAG_START_MOVE_BG_MSG,(Ref*)TAG_START_MOVE_BG_MSG);
}

void Player::stopRun()
{
	m_isRunning = false;
	AUDIOENGINE->stopAllEffects();
	
	if (m_entityStatus != BaseEntity::EntityStatus::en_Jump_Status)
	{
		this->stopAllActions();
		m_timeline->gotoFrameAndPause(0);
		m_entityStatus = BaseEntity::EntityStatus::en_Stop_Status;
		this->unscheduleUpdate();
		NOTIFY->postNotification(TAG_STOP_MOVE_BG_MSG, (Ref*)TAG_STOP_MOVE_BG_MSG);
	}
}

void Player::onWalk()
{
}

void Player::jump(int high)
{
	if (m_entityStatus == BaseEntity::EntityStatus::en_Jump_Status )
	{
		return;
	}
	
	this->stopAllActions();
	m_timeline->gotoFrameAndPause(0);

	if (m_timeline->IsAnimationInfoExists(JUMP_ANIMATION_NAME))
	{
		auto animInfo = m_timeline->getAnimationInfo(JUMP_ANIMATION_NAME);

		m_timeline->play(JUMP_ANIMATION_NAME, false);	// ����������
		
		/* ���� */
		auto jumpBy = JumpBy::create(jumpTime ,Vec2(high / 2,0), high,1);
		auto call = CallFunc::create([&]() {
			m_entityStatus = BaseEntity::EntityStatus::en_Stop_Status;
			this->stopAllActions();
			this->unscheduleUpdate();
			NOTIFY->postNotification(TAG_STOP_MOVE_BG_MSG, (Ref*)TAG_STOP_MOVE_BG_MSG);

			if (m_isRunning)
			{
				run(false);
				return;
			}

		});

		this->runAction(Sequence::create(jumpBy,call,nullptr));

		if (!this->isScheduled(schedule_selector(Player::update)))
		{
			this->scheduleUpdate();
		}
	}

	m_entityStatus = BaseEntity::EntityStatus::en_Jump_Status;
	NOTIFY->postNotification(TAG_START_MOVE_BG_MSG, (Ref*)TAG_START_MOVE_BG_MSG);
}

void Player::setViewPointByPlayer()
{
	if (m_sprite == nullptr)
	{
		return;
	}

	auto parent = getParent();	//player��parentΪ��ͼ

	/* ��ͼ�������� */
	Size mapTiledNum = m_map->getMapSize();

	/* ��ͼ�������Ӵ�С */
	Size tiledSize = m_map->getTileSize();

	/* ��ͼ��С */
	Size mapSize = Size(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);

	/* ��Ļ��С */
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/* �������� */
	Point spritePos = getPosition();

	/* �����������С����Ļһ�룬��ȡ��Ļ�е����꣬��֮ȡ�������� */
	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	/* ���x,y����������ϽǼ���ֵ����ȡ����ֵ���� */
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	/* Ŀ��� */
	Point destPos = Point(x, y);

	/* ��Ļ�е� */
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	/* ������Ļ�е��Ŀ���֮����� */
	Point viewPos = centerPos - destPos;

	parent->setPosition(viewPos);
}

void Player::setTagPosition(int x, int y)
{
	if (m_metaLayer == nullptr)
	{
		/* ������Ϊ�����ƶ���ͼ */
		setViewPointByPlayer();
		return;
	}

	/* ------------------ �ж�ǰ���Ƿ����ͨ�� ----------------------- */

	/* ȡ����ǰ������ */
	Size spriteSize = this->getContentSize();
	Point dstPos = Point(x + spriteSize.width / 2, y);

	/* ��ȡ���ǵ�ǰǰ�������ڵ�ͼ�еĸ���λ�� */
	Point tiledPos = tileCoordForPosition(dstPos);

	/* ��ȡ��ͼ����Ψһ��ʶ */
	int tiledGid = m_metaLayer->getTileGIDAt(tiledPos);

	/* ��Ϊ0���������������� */
	if (tiledGid != 0)
	{
		/* ��ȡ�õ�ͼ������������ */
		Value properties = m_map->getPropertiesForGID(tiledGid);

		if (!properties.isNull())
		{
			ValueMap propertiesMap = properties.asValueMap();

			if (propertiesMap.find("Collidable") != propertiesMap.end())
			{
				/* ��ȡ���ӵ�Collidable���� */
				Value prop = propertiesMap.at("Collidable");

				/* �ж�Collidable�Ƿ�Ϊtrue������������ƶ� */
				if (prop.asString().compare("true") == 0 && m_isRebound == false)
				{
					m_isRebound = true;

					auto jumpBy = JumpBy::create(0.5f, Point(-100, 0), 80, 1);
					CallFunc* callFunc = CallFunc::create([&]() {
						/* �ָ�״̬ */
						m_isRebound = false;
					});

					/* ִ�ж��� */
					auto actions = Sequence::create(jumpBy, callFunc, NULL);
					this->runAction(actions);

					return;
				}
			}

			if (propertiesMap.find("food") != propertiesMap.end())
			{
				/* ȡ�ø���food���ԣ������food����food��ʧ */
				Value prop = propertiesMap.at("food");
				if (prop.asString().compare("true") == 0)
				{
					/* ���ϰ�����������ǰ������Ʒ */
					experimental::TMXLayer* barrier = m_map->getLayer("barrier");
					barrier->removeTileAt(tiledPos);
				}
			}

			if (propertiesMap.find("win") != propertiesMap.end())
			{
				/* ȡ�ø���win���ԣ������win������Ϸ���� */
				Value prop = propertiesMap.at("win");
				if (prop.asString().compare("true") == 0)
				{
					/* ����ʤ������ */
					//SceneManager::getInstance()->changeCurSceneType(SceneType::en_Tollgate_Scene);
				}
			}
		}
	}

	//setPosition(x, y);

	/* ������Ϊ�����ƶ���ͼ */
	setViewPointByPlayer();
}

void Player::setTiedMap(experimental::TMXTiledMap * map)
{
	m_map = map;
	m_metaLayer = map->getLayer(META_LAYER);
}

void Player::update(float dt)
{
	//setViewPointByPlayer();
	setTagPosition(getPositionX(),getPositionY());
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

void Player::onBindSprite()
{
	BaseEntity::onBindSprite();

	m_timeline->gotoFrameAndPlay(0);
	m_sprite->runAction(m_timeline);
	m_timeline->gotoFrameAndPause(0);

}

void Player::loadPlayerAnimation(const std::string fileName)
{
	m_timeline = CSLoader::createTimeline(fileName);
	m_timeline->setTimeSpeed(1);
	m_timeline->retain();

	auto anim = m_timeline->getAnimationInfo(RUN_ANIMATION_NAME);
	runTime = (anim.endIndex - anim.startIndex) / 60.0f;

	anim = m_timeline->getAnimationInfo(JUMP_ANIMATION_NAME);
	jumpTime = (anim.endIndex - anim.startIndex) / 60.0f;

}

void Player::setPlayerProperties(int iRow,const char* csvFilePath)
{
	m_id = CsvUtil::getInstance()->getInt(iRow, 1, csvFilePath);
	m_modelId = CsvUtil::getInstance()->getInt(iRow, 2, csvFilePath);
	m_entityName = CsvUtil::getInstance()->getString(iRow, 3, csvFilePath);
	m_level = CsvUtil::getInstance()->getInt(iRow, 4, csvFilePath);
	m_lifeValue = CsvUtil::getInstance()->getInt(iRow, 5, csvFilePath);
	m_speed = CsvUtil::getInstance()->getFloat(iRow, 6, csvFilePath);
	m_defense = CsvUtil::getInstance()->getFloat(iRow, 7, csvFilePath);
	m_curAct = CsvUtil::getInstance()->getInt(iRow, 8, csvFilePath);
}

void Player::movePos(float dt,float dis)
{
	auto call = CallFunc::create([&]() {
		movePos(runTime, m_speed);
	});
	MoveBy* move = nullptr;

	if (m_isLeftMove)
	{
		move = MoveBy::create(dt, Vec2(-dt * dis, 0));
	}
	else
	{
		move = MoveBy::create(dt, Vec2(dt * dis, 0));
	}

	auto seq = Sequence::create(move, call, nullptr);
	this->runAction(seq);

	return;
}


/* �����Ƿ����� */
void Player::setIsLeftMove(bool isLeft)
{
	m_isLeftMove = isLeft;
}

Point Player::tileCoordForPosition(Point pos)
{
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();

	int x = pos.x / tiledSize.width;

	/* cocos Ĭ��y�����µ��ϣ�������� */
	int y = (WINSIZE.height - pos.y) / tiledSize.height;

	/* ���������0��ʼ���� */
	if (x > 0)
	{
		x -= 1;
	}

	if (y > 0)
	{
		y -= 0;
	}


	return Point(x, y);
}
