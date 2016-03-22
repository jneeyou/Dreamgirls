#include "BaseEntity.h"

bool BaseEntity::init()
{
	return true;
}

void BaseEntity::AttackedHurt(int hurtValue)
{
}

Sprite * BaseEntity::getSprite()
{
	return nullptr;
}

void BaseEntity::movePos()
{
	return ;
}

void BaseEntity::onBindSprite()
{
}

void BaseEntity::onDead()
{
}

void BaseEntity::onHurt(int hurtValue)
{
}

void BaseEntity::bindSprite()
{
}

void BaseEntity::dead()
{
}
