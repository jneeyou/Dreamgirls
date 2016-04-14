#include "TollgateScene.h"
#include "Player.h"

/* 关卡地图文件名 */
#define TMX_TILEDMAP_FILE_OF_TOLLGATE(x) ("level/lv_" + Value(x).asString() + ".tmx")

/* 主角图片名 */
#define PLAYER_SPRITE_NAME	"GirlRes/girl.png"

/* 第一关地图背景名 */
#define LV_ONE_MAP_BG	"level/lv_1_map_bg.png"


TollgateScene::TollgateScene()
{
}

TollgateScene::~TollgateScene()
{
	this->stopAllActions();
	this->removeAllChildrenWithCleanup(true);

	auto instance = TextureCache::getInstance();
	switch (m_curLevel)
	{
	case 1:
		instance->removeTextureForKey(LV_1_RES_1);
		instance->removeTextureForKey(LV_1_RES_2);
		instance->removeTextureForKey(LV_1_RES_3);
		break;
	case 2:
		instance->removeTextureForKey(LV_2_RES_1);
		break;
	case 3:
		instance->removeTextureForKey(LV_3_RES_1);
		break;
	case 4:
		instance->removeTextureForKey(LV_4_RES_1);
		break;
	case 5:
		instance->removeTextureForKey(LV_5_RES_1);
		break;
	case 6:
		instance->removeTextureForKey(LV_6_RES_1);
		break;
	case 7:
		instance->removeTextureForKey(LV_7_RES_1);
		break;
	case 8:
		instance->removeTextureForKey(LV_8_RES_1);
		break;
	case 9:
		instance->removeTextureForKey(LV_9_RES_1);
		break;
	case 10:
		instance->removeTextureForKey(LV_10_RES_1);
		break;
	}
}

Scene * TollgateScene::createScene(const char * filepath)
{
	auto scene = Scene::createWithPhysics();
	auto layer = TollgateScene::create(filepath);
	scene->addChild(layer);

	/* 显示调试框 */
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	/* 设置重力 */
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0.0f));

	return scene;
}

bool TollgateScene::init(const char * filePath)
{
	/* 初始化图层对象 */
	m_mapLayer = TollgateMapLayer::create();
	this->addChild(m_mapLayer);

	m_logicLayer = TollgateLogicLayer::create();
	this->addChild(m_logicLayer);

	m_bgLayer = TollgatBgLayer::create();
	this->addChild(m_bgLayer);

	m_spalshLayer = TollgateSplashLayer::create();
	this->addChild(m_spalshLayer);

	DIRECTOR->setProjection(Director::Projection::_2D);

	if (!BaseScene::init(filePath))
	{
		return false;
	}

	/* 添加监听 */
	auto touchEvent = EventListenerTouchOneByOne::create();
	touchEvent->onTouchBegan = CC_CALLBACK_2(TollgateScene::onTouchBegan,this);
	touchEvent->onTouchEnded = CC_CALLBACK_2(TollgateScene::onTouchEnded, this);
	touchEvent->onTouchMoved = CC_CALLBACK_2(TollgateScene::onTouchMoved, this);

	log("init");

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

void TollgateScene::update(float dt)
{
	
}

void TollgateScene::setControllerInBgLayer()
{
	BaseScene::init();

	/* 绑定逻辑层 */
	auto logic = dynamic_cast<Node*>(bgLayer->getChildByName("logicLayer"));
	m_logicLayer->bindLayer(logic);
	logic->setLocalZOrder(3);

	/* 绑定背景层 */
	auto bg = dynamic_cast<Node*>(bgLayer->getChildByName("bgLayer"));
	m_bgLayer->bindLayer(bg);
	bg->setLocalZOrder(1);

	/* 获得当前关卡 */
	m_curLevel = getIntFromXML(CURRENT_TOLLGATE, 1);
	loadMapResurce();

}

void TollgateScene::addPlayer(experimental::TMXTiledMap * tiledMap)
{
	m_player = Player::create(PATH_CSV_PLAYER);
	tiledMap->addChild(m_player,2);

	auto sp = (SkeletonNode*)CSLoader::createNode(PATH_PLAYER_AIMATION_FILE);

	m_player->bindSprite(sp);
	m_player->setPosition(Vec2(100, 128 + 25));

	m_player->setTiedMap(tiledMap);

	/* 创建物理身体 */
	auto body = PhysicsBody::createBox(m_player->getBoundingBox().size);
	m_player->setPhysicsBody(body);
	//log("%f,%f", sp->getContentSize().width, sp->getContentSize().height);
}

void TollgateScene::firstEnterGame()
{
	/* 添加地图背景 */
	auto bgg = Sprite::create(LV_ONE_MAP_BG);
	bgg->setName(LV_ONE_MAP_BG);
	this->addChild(bgg, 1);
	bgg->setAnchorPoint(Vec2(0, 0));

	/* 添加遮罩 */
	auto cLayer = LayerColor::create(Color4B(255, 255, 255, 255));
	cLayer->setName("cLayer");
	this->addChild(cLayer, 2);
	auto out = FadeOut::create(3.0f);
	auto call = CallFunc::create([&]() {
		/* 移动玩家 */
		auto sp = this->getChildByName("lv_sp");
		auto tl = CSLoader::createTimeline(PATH_PLAYER_AIMATION_FILE);
		tl->setTimeSpeed(1);
		sp->runAction(tl);

		tl->play("run", false);
		tl->gotoFrameAndPause(0);
		tl->play("run", true);
		sp->setPosition(Vec2(100, 153));
		
		auto mv = MoveTo::create(8.0f, Vec2(WINSIZE.width, 153));
		auto call2 = CallFunc::create([&]() {
			auto player = this->getChildByName("lv_sp");
			player->stopAllActions();

			auto cLayer = this->getChildByName("cLayer");
			auto in = FadeIn::create(1.0f);
			auto call = CallFunc::create([&]() {
				this->removeChildByName(LV_ONE_MAP_BG, true);
				this->removeChildByName("lv_sp", true);

				/* 添加玩家 */
				addPlayer(m_mapLayer->getMap());

				/*逻辑层绑定玩家 */
				m_logicLayer->bindPlayer(m_player);
				bgLayer->getChildByName("logicLayer")->setVisible(true);
			});
			auto out = FadeOut::create(1.0f);
			auto calls = CallFunc::create([&]() {
				this->removeChild(cLayer, true);
			});
			auto seq = Sequence::create(in, call, out, calls, nullptr);
			cLayer->runAction(seq);
		});
		sp->runAction(Sequence::create(mv, call2, nullptr));
	});
	cLayer->runAction(Sequence::create(out,call,nullptr));

	auto sp = (SkeletonNode*)CSLoader::createNode(PATH_PLAYER_AIMATION_FILE);
	sp->setName("lv_sp");
	sp->setAnchorPoint(Vec2(0, 0));
	this->addChild(sp, 1);
	sp->setPosition(Vec2(100, 128));
}

void TollgateScene::onEnter()
{
	BaseScene::onEnter();

	auto body = PhysicsBody::createEdgeBox(WINSIZE, PHYSICSBODY_MATERIAL_DEFAULT,2);
	auto edge = Node::create();
	edge->setPhysicsBody(body);
	edge->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	this->addChild(edge);

	log("enter");
}

void TollgateScene::loadMapResurce()
{
	m_loadResCnt = 0;
	switch (m_curLevel)
	{
	case 1:
		LOAD_IMAGE_ASYNC(LV_1_RES_1, TollgateScene::imageLoadCallFunc);
		break;
	case 2:
		LOAD_IMAGE_ASYNC(LV_2_RES_1, TollgateScene::imageLoadCallFunc);
		break;
	case 3:
		LOAD_IMAGE_ASYNC(LV_3_RES_1, TollgateScene::imageLoadCallFunc);
		break;
	case 4:
		LOAD_IMAGE_ASYNC(LV_4_RES_1, TollgateScene::imageLoadCallFunc);
		break;
	case 5:
		LOAD_IMAGE_ASYNC(LV_5_RES_1, TollgateScene::imageLoadCallFunc);
		break;
	case 6:
		LOAD_IMAGE_ASYNC(LV_6_RES_1, TollgateScene::imageLoadCallFunc);
		break;
	case 7:
		LOAD_IMAGE_ASYNC(LV_7_RES_1, TollgateScene::imageLoadCallFunc);
		break;
	case 8:
		LOAD_IMAGE_ASYNC(LV_8_RES_1, TollgateScene::imageLoadCallFunc);
		break;
	case 9:
		LOAD_IMAGE_ASYNC(LV_9_RES_1, TollgateScene::imageLoadCallFunc);
		break;
	case 10:
		LOAD_IMAGE_ASYNC(LV_10_RES_1, TollgateScene::imageLoadCallFunc);
		break;
	}
}

/* 图片加载回调函数 */
void TollgateScene::imageLoadCallFunc(Texture2D* texture)
{
	m_loadResCnt++;
	if (m_curLevel == 1)
	{
		/*if (m_loadResCnt == 1)
		{
			LOAD_IMAGE_ASYNC(LV_1_RES_2, TollgateScene::imageLoadCallFunc);
			return;
		}
		else if (m_loadResCnt == 2)
		{
			LOAD_IMAGE_ASYNC(LV_1_RES_3, TollgateScene::imageLoadCallFunc);
			return;
		}*/
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("level/lv_1_res.plist", texture);
	}
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	log(TextureCache::getInstance()->getCachedTextureInfo().c_str());
#endif

	ETMXTileMap* map = nullptr;
	if (m_curLevel == 1)
	{
		map = ETMXTileMap::create("level/lv_" + Value(m_curLevel).asString() + ".tmx");
	}
	else
	{
		map = ETMXTileMap::create(TMX_TILEDMAP_FILE_OF_TOLLGATE(m_curLevel));
	}

	bgLayer->addChild(map, 2);

	m_mapLayer->bindMap(map);

	// 第一次进入
	if (getBoolFromXML(USER_FIRST_ENTER, true))
	{
		firstEnterGame();
		m_logicLayer->getLayer()->setVisible(false);

		setBoolToXML(USER_FIRST_ENTER, false);
		USERDEFAULT->flush();
	}
	else
	{
		/* 添加玩家 */
		addPlayer(map);

		/*逻辑层绑定玩家 */
		m_logicLayer->bindPlayer(m_player);
	}

}

