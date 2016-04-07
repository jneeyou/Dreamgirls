#include "TollgateScene.h"
#include "Player.h"

/* 关卡地图文件名 */
#define TMX_TILEDMAP_FILE_OF_TOLLGATE(x) ("tmx_tiledmap_of_tollgate" + Value(x).asString() + ".tmx")

/* 主角图片名 */
#define PLAYER_SPRITE_NAME	"GirlRes/girl.png"


bool TollgateScene::init(const char * filePath)
{
	m_scoreLabel = nullptr;

	if (!BaseScene::init(filePath))
	{
		return false;
	}

	/* 添加地图 */
	int level = getIntFromXML(CURRENT_TOLLGATE,1);
	TMXTiledMap* map = TMXTiledMap::create(TMX_TILEDMAP_FILE_OF_TOLLGATE(level));

	/* 添加玩家 */
	addPlayer(map);

	/* 移动背景 */
	schedule(schedule_selector(TollgateScene::moveBg));

	/* 添加监听 */
	auto touchEvent = EventListenerTouchOneByOne::create();
	touchEvent->onTouchBegan = CC_CALLBACK_2(TollgateScene::onTouchBegan,this);
	touchEvent->onTouchEnded = CC_CALLBACK_2(TollgateScene::onTouchEnded, this);
	touchEvent->onTouchMoved = CC_CALLBACK_2(TollgateScene::onTouchMoved, this);

	return true;
}

bool TollgateScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	return true;
}

void TollgateScene::onTouchMoved(Touch * touch, Event * unused_event)
{
}

void TollgateScene::onTouchEnded(Touch * touch, Event * unused_event)
{
}

void TollgateScene::setControllerInBgLayer()
{
	BaseScene::init();

	rightMoveBtn = dynamic_cast<Button*>(bgLayer->getChildByName(TOLLGATE_SCENE_RIGHT_MOVE_BTN));
	jumpBtn = dynamic_cast<Button*>(bgLayer->getChildByName(TOLLGATE_SCENE_JUMP_BTN));
	pauseBtn = dynamic_cast<Button*>(bgLayer->getChildByName(TOLLGATE_SCENE_PAUSE_BTN));

	m_scoreLabel = dynamic_cast<TextBMFont*>(bgLayer->getChildByName(TOLLGATE_SCENE_SCORE_LABEL));

	// 右移事件
	rightMoveBtn->addTouchEventListener([&](Ref* ref, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			PLAY_EFFECT(PATH_RUN_SOUND, true);
			rightMoveBtn->runAction(ScaleTo::create(0.1f, 1.2f));

			m_player->run(false);
		}
		else if (type == Widget::TouchEventType::MOVED)
		{
			auto ePos = rightMoveBtn->getTouchMovePosition();
			auto sPos = rightMoveBtn->getPosition();
			auto dis = sPos.distance(ePos);
			
			if (dis > rightMoveBtn->getContentSize().width / 2)
			{
				m_player->stopRun();
			}
		}
		else
		{
			rightMoveBtn->runAction(ScaleTo::create(0.1f, 1.0f));
			m_player->stopRun();
		}
	});

	// 跳跃事件
	jumpBtn->addTouchEventListener([&](Ref* ref, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			PLAY_EFFECT(PATH_JUMP_SOUND, false);
			jumpBtn->runAction(ScaleTo::create(0.1f, 1.2f));
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			m_player->jump(150);
			jumpBtn->runAction(ScaleTo::create(0.1f, 1.0f));
		}
	});

	// 暂停
	pauseBtn->addTouchEventListener([&](Ref* ref, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			PLAY_EFFECT(PATH_BUTTON_SOUND, false);
			pauseBtn->runAction(ScaleTo::create(0.1f, 1.1f));
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			// 显示暂停层
			pauseBtn->runAction(ScaleTo::create(0.1f, 1.0f));
		}
	});

	//初始分数值
	m_scoreLabel->setString("score: 0 km");

	m_bottomBg = dynamic_cast<Sprite*>(bgLayer->getChildByName("bg"));

}

void TollgateScene::addPlayer(TMXTiledMap * tiledMap)
{
	m_player = Player::create(PATH_CSV_PLAYER);
	addChild(m_player);

	auto sp = (SkeletonNode*)CSLoader::createNode(PATH_PLAYER_AIMATION_FILE);

	m_player->bindSprite(sp);
	m_player->setPosition(Vec2(20, 30));
}

void TollgateScene::moveBg(float dt)
{
	//m_bottomBg->setPositionX(m_bottomBg->getPositionX() + 1);

}
