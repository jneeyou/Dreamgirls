#include "Player.h"
#include "CsvUtil.h"
#include "SceneManager.h"
#include "GlobalDefine.h"

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

	m_isRebound = false;
	runTime = 0;
	jumpTime = 0;

	/* 通过配置文件设置属性 */
	setPlayerProperties(csvFilePath);

	/* 获取动画 */
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

	/* 设置方向 */
	setIsLeftMove(isLeft);

	/* 停止所有动作 */
	this->stopAllActions();
	m_timeline->gotoFrameAndPause(0);

	if (m_sprite != nullptr)
	{
		if (m_timeline->IsAnimationInfoExists(RUN_ANIMATION_NAME))
		{
			m_timeline->play(RUN_ANIMATION_NAME, true);	// 播放跑动画
		}
	}

	/* 移动位置 */
	movePos(runTime, 80);

	m_entityStatus = BaseEntity::EntityStatus::en_Run_Status;
}

void Player::stopRun()
{
	AUDIOENGINE->stopAllEffects();
	m_timeline->gotoFrameAndPause(0);
	this->stopAllActions();
	m_entityStatus = BaseEntity::EntityStatus::en_Stop_Status;
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

		m_timeline->play(JUMP_ANIMATION_NAME, false);	// 播放跳动画
		
		/* 跳动 */
		auto jumpBy = JumpBy::create(jumpTime ,Vec2(high / 2,0), high,1);
		auto call = CallFunc::create([&]() {
			m_entityStatus = BaseEntity::EntityStatus::en_Stop_Status;
			this->stopAllActions();
		});

		this->runAction(Sequence::create(jumpBy,call,nullptr));
	}

	m_entityStatus = BaseEntity::EntityStatus::en_Jump_Status;
}

void Player::setViewPointByPlayer()
{
	if (m_sprite == nullptr)
	{
		return;
	}

	Layer* parent = (Layer*)getParent();	//player的parent为地图

	/* 地图方块数量 */
	Size mapTiledNum = m_map->getMapSize();

	/* 地图单个格子大小 */
	Size tiledSize = m_map->getTileSize();

	/* 地图大小 */
	Size mapSize = Size(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);

	/* 屏幕大小 */
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/* 主角坐标 */
	Point spritePos = getPosition();

	/* 如果主角坐标小于屏幕一半，则取屏幕中点坐标，反之取主角坐标 */
	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	/* 如果x,y坐标大于右上角极限值，则取极限值坐标 */
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	/* 目标点 */
	Point destPos = Point(x, y);

	/* 屏幕中点 */
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	/* 计算屏幕中点和目标点之间距离 */
	Point viewPos = centerPos - destPos;

	parent->setPosition(viewPos);
}

void Player::setTagPosition(int x, int y)
{
	/* ------------------ 判断前面是否可以通行 ----------------------- */

	/* 取主角前方坐标 */
	Size spriteSize = m_sprite->getContentSize();
	Point dstPos = Point(x + spriteSize.width / 2, y);

	/* 获取主角当前前方坐标在地图中的格子位置 */
	Point tiledPos = tileCoordForPosition(dstPos);

	/* 获取地图格子唯一标识 */
	int tiledGid = m_metaLayer->getTileGIDAt(tiledPos);

	/* 不为0，代表存在这个格子 */
	if (tiledGid != 0)
	{
		/* 获取该地图格子所有属性 */
		Value properties = m_map->getPropertiesForGID(tiledGid);

		ValueMap propertiesMap = properties.asValueMap();

		if (propertiesMap.find("Collidable") != propertiesMap.end())
		{
			/* 获取格子的Collidable属性 */
			Value prop = propertiesMap.at("Collidable");

			/* 判断Collidable是否为true，是则不让玩家移动 */
			if (prop.asString().compare("true") == 0 && m_isRebound == false)
			{
				m_isRebound = true;

				auto jumpBy = JumpBy::create(0.5f, Point(-100, 0), 80, 1);
				CallFunc* callFunc = CallFunc::create([&]() {
					/* 恢复状态 */
					m_isRebound = false;
				});

				/* 执行动作 */
				auto actions = Sequence::create(jumpBy, callFunc, NULL);
				this->runAction(actions);

				return;
			}
		}

		if (propertiesMap.find("food") != propertiesMap.end())
		{
			/* 取得格子food属性，如果是food，让food消失 */
			Value prop = propertiesMap.at("food");
			if (prop.asString().compare("true") == 0)
			{
				/* 从障碍物物层清除当前格子物品 */
				TMXLayer* barrier = m_map->getLayer("barrier");
				barrier->removeTileAt(tiledPos);
			}
		}

		if (propertiesMap.find("win") != propertiesMap.end())
		{
			/* 取得格子win属性，如果是win，则游戏结束 */
			Value prop = propertiesMap.at("win");
			if (prop.asString().compare("true") == 0)
			{
				/* 跳到胜利场景 */
				//SceneManager::getInstance()->changeCurSceneType(SceneType::en_Tollgate_Scene);
			}
		}
	}

	setPosition(x, y);

	/* 以主角为中心移动地图 */
	setViewPointByPlayer();
}

void Player::setTiedMap(TMXTiledMap * map)
{
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
	m_timeline->retain();

	auto anim = m_timeline->getAnimationInfo(RUN_ANIMATION_NAME);
	runTime = (anim.endIndex - anim.startIndex) / 60.0f;

	anim = m_timeline->getAnimationInfo(JUMP_ANIMATION_NAME);
	jumpTime = (anim.endIndex - anim.startIndex) / 60.0f;

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

void Player::movePos(float dt,float dis)
{
	auto call = CallFunc::create([&]() {
		movePos(runTime, 80);
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


/* 设置是否左移 */
void Player::setIsLeftMove(bool isLeft)
{
	m_isLeftMove = isLeft;
}

Point Player::tileCoordForPosition(Point pos)
{
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();

	int x = pos.x / tiledSize.width;

	/* cocos 默认y是由下到上，做个相减 */
	int y = (WINSIZE.height - pos.y) / tiledSize.height;

	/* 格子坐标从0开始计算 */
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
