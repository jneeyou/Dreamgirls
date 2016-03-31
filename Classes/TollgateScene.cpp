#include "TollgateScene.h"
#include "Player.h"

/* �ؿ���ͼ�ļ��� */
#define TMX_TILEDMAP_FILE_OF_TOLLGATE(x) ("tmx_tiledmap_of_tollgate" + Value(x).asString() + ".tmx")

/* ����ͼƬ�� */
#define PLAYER_SPRITE_NAME	"GirlRes/girl.png"


bool TollgateScene::init(const char * filePath)
{
	if (!BaseScene::init(filePath))
	{
		return false;
	}

	m_scoreLabel = nullptr;

	/* ��ӵ�ͼ */
	int level = getIntFromXML(CURRENT_TOLLGATE,1);
	TMXTiledMap* map = TMXTiledMap::create(TMX_TILEDMAP_FILE_OF_TOLLGATE(level));

	/* ������ */
	addPlayer(map);

	/* �ƶ����� */
	schedule(schedule_selector(TollgateScene::moveBg));

	return true;
}

void TollgateScene::setControllerInBgLayer()
{
	BaseScene::init();

	auto leftMoveBtn = dynamic_cast<Button*>(bgLayer->getChildByName(TOLLGATE_SCENE_LEFT_MOVE_BTN));
	auto rightMoveBtn = dynamic_cast<Button*>(bgLayer->getChildByName(TOLLGATE_SCENE_RIGHT_MOVE_BTN));
	auto jumpBtn = dynamic_cast<Button*>(bgLayer->getChildByName(TOLLGATE_SCENE_JUMP_BTN));
	auto pauseBtn = dynamic_cast<Button*>(bgLayer->getChildByName(TOLLGATE_SCENE_PAUSE_BTN));

	m_scoreLabel = dynamic_cast<TextBMFont*>(bgLayer->getChildByName(TOLLGATE_SCENE_SCORE_LABEL));

	// �����¼�
	leftMoveBtn->addTouchEventListener([&](Ref* ref, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			PLAY_EFFECT(PATH_RUN_SOUND, false);
			m_player->runAction(MoveBy::create(0.4f, Vec2(-5, 0)));
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			
		}
	});

	// �����¼�
	rightMoveBtn->addTouchEventListener([&](Ref* ref, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			PLAY_EFFECT(PATH_RUN_SOUND, false);
			m_player->runAction(MoveBy::create(0.4f, Vec2(5, 0)));
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			
		}
	});

	// ��Ծ�¼�
	jumpBtn->addTouchEventListener([&](Ref* ref, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			PLAY_EFFECT(PATH_JUMP_SOUND, false);
		}

		if (type == Widget::TouchEventType::ENDED)
		{

		}
	});

	// ��ͣ
	pauseBtn->addTouchEventListener([&](Ref* ref, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			PLAY_EFFECT(PATH_BUTTON_SOUND, false);
		}

		if (type == Widget::TouchEventType::ENDED)
		{

		}
	});

	//��ʼ����ֵ
	m_scoreLabel->setString("score: 0 km");

	m_bottomBg = dynamic_cast<Sprite*>(bgLayer->getChildByName("bg"));

}

void TollgateScene::addPlayer(TMXTiledMap * tiledMap)
{
	m_player = Player::create(PATH_CSV_PLAYER);
	addChild(m_player);

	auto sp = (SkeletonNode*)CSLoader::createNode(PATH_PLAYER_AIMATION_FILE);
	
	m_player->bindSprite(sp);
	m_player->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2));
	m_player->run();
}

void TollgateScene::moveBg(float dt)
{
	//m_bottomBg->setPositionX(m_bottomBg->getPositionX() + 1);

}
