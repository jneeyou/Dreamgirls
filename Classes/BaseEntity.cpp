#include "BaseEntity.h"
#include "GlobalDefine.h"


BaseEntity::BaseEntity()
{
	m_sprite = nullptr;
	m_speed = 0;
	m_lifeValue = 100;
	m_id = -1;
	m_modelId = -1;
	m_entityName = "";
	m_level = 0;
	m_defense = 0;

	m_entityStatus = EntityStatus::en_Stop_Status;
}

BaseEntity::~BaseEntity()
{
	NOTIFY->removeAllObservers(this);
}

bool BaseEntity::init()
{
	return true;
}

void BaseEntity::AttackedHurt(int hurtValue)
{
	stopAllActions();

	// 播放特效

	// 播放音效

	// 受伤
	onHurt(hurtValue);
}

SkeletonNode * BaseEntity::getSprite()
{
	return m_sprite;
}

void BaseEntity::movePos(float dt, float dis)
{
}

void BaseEntity::onBindSprite()
{
	auto size = m_sprite->getContentSize();
	this->setContentSize(size);

}

void BaseEntity::onDead()
{
	stopAllActions();

	// 发送死亡消息
	NOTIFY->postNotification("dead",nullptr);
}

void BaseEntity::onHurt(int hurtValue)
{
	m_lifeValue -= hurtValue;
	if (m_lifeValue <= 0)
	{
		m_lifeValue = 0;
		onDead();
	}
}

void BaseEntity::bindSprite(SkeletonNode* sprite)
{
	assert(sprite);

	m_sprite = sprite;
	this->addChild(m_sprite);

	onBindSprite();
}

void BaseEntity::setEntityStatus(EntityStatus status)
{
	m_entityStatus = status;
}

BaseEntity::EntityStatus BaseEntity::getEntityStatus()
{
	return m_entityStatus;
}
