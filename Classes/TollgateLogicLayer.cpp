#include "TollgateLogicLayer.h"
#include "GlobalDefine.h"
#include "Player.h"
#include "PauseLayer.h"
#include "PauseLayer.h"


TollgateLogicLayer::TollgateLogicLayer()
{
	m_layer = nullptr;
	m_player = nullptr;
}

TollgateLogicLayer::~TollgateLogicLayer()
{
	NOTIFY->removeAllObservers(this);
}

bool TollgateLogicLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}

void TollgateLogicLayer::bindLayer(Node * layer)
{
	CC_ASSERT(layer);

	m_layer = layer;
	setControlLayer();
}

void TollgateLogicLayer::bindPlayer(Player * player)
{
	CC_ASSERT(player);
	m_player = player;
}

void TollgateLogicLayer::setControlLayer()
{
	if (m_layer == nullptr)
	{
		return;
	}

	rightMoveBtn = dynamic_cast<Button*>(m_layer->getChildByName(TOLL_LOGIC_LAYER_RIGHT_MOVE_BTN));
	jumpBtn = dynamic_cast<Button*>(m_layer->getChildByName(TOLL_LOGIC_LAYER_JUMP_BTN));
	pauseBtn = dynamic_cast<Button*>(m_layer->getChildByName(TOLL_LOGIC_LAYER_PAUSE_BTN));

	m_scoreLabel = dynamic_cast<TextBMFont*>(m_layer->getChildByName(TOLL_LOGIC_LAYER_SCORE_LABEL));

	// 右移事件
	rightMoveBtn->addTouchEventListener([&](Ref* ref, Widget::TouchEventType type) {
		if (m_layer == nullptr)
		{
			return;
		}

		if (type == Widget::TouchEventType::BEGAN)
		{
			if (Effect_State)
			{
				PLAY_EFFECT(PATH_RUN_SOUND, true);
			}
			rightMoveBtn->runAction(ScaleTo::create(0.05f, 0.75f));
			log("scale:%f", rightMoveBtn->getScale());

			m_player->run(false);
		}
		else if (type == Widget::TouchEventType::MOVED)
		{
			auto ePos = rightMoveBtn->getTouchMovePosition();
			auto sPos = rightMoveBtn->getPosition();
			auto dis = sPos.distance(ePos);

			if (dis > rightMoveBtn->getContentSize().width / 2 * rightMoveBtn->getScale())
			{
				m_player->stopRun();
			}
		}
		else
		{
			rightMoveBtn->runAction(ScaleTo::create(0.05f, 0.65f));
			m_player->stopRun();
		}
	});

	// 跳跃事件
	jumpBtn->addTouchEventListener([&](Ref* ref, Widget::TouchEventType type) {
		if (m_layer == nullptr)
		{
			return;
		}

		if (type == Widget::TouchEventType::BEGAN)
		{
			if (Effect_State)
			{
				PLAY_EFFECT(PATH_JUMP_SOUND, false);
			}
			jumpBtn->runAction(ScaleTo::create(0.05f, 0.75f));
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			m_player->jump(150);
			jumpBtn->runAction(ScaleTo::create(0.05f, 0.65));
		}
	});

	// 暂停
	pauseBtn->addTouchEventListener([&](Ref* ref, Widget::TouchEventType type) {
		if (m_layer == nullptr)
		{
			return;
		}

		if (type == Widget::TouchEventType::BEGAN)
		{
			if (Effect_State)
			{
				PLAY_EFFECT(PATH_BUTTON_SOUND, false);
			}
			pauseBtn->runAction(ScaleTo::create(0.1f, 1.1f));
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			// 显示暂停层
			pauseBtn->runAction(ScaleTo::create(0.1f, 1.0f));

			auto layer = PauseLayer::create();
			layer->setName("pauseLayer");
			m_layer->getParent()->addChild(layer);
			m_layer->getParent()->addChild(layer->getBgLayer(), 5);

		}
	});

	//初始分数值
	//m_scoreLabel->setString("score: 0 km");
}
