#include "StartScene.h"
#include "SceneManager.h"
#include "GlobalDefine.h"
#include "SettingLayer.h"
#include "HelpLayer.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::init(const char* filePath)
{
	if (!BaseScene::init(filePath))
	{
		return false;
	}

	/* 播放音乐 */
	if (getBoolFromXML(BGM_KEY,true))
	{
		PLAY_MUSIC(PATH_BGM_SOUND, true);
	}

	/* 添加粒子 */
	auto particle1 = ParticleSystemQuad::create("guangtuan.plist");
	auto particle2 = ParticleSystemQuad::create("guangtuan.plist");
	auto particle3 = ParticleSystemQuad::create("chuanyue.plist");

	particle1->setPosition(ccp(WINSIZE.width / 4 - 10, WINSIZE.height / 2));
	particle2->setPosition(ccp(WINSIZE.width / 4 * 3 + 10, WINSIZE.height / 2));
	particle3->setPosition(ccp(WINSIZE.width / 2, WINSIZE.height - 100));

	auto batchNode1 = ParticleBatchNode::createWithTexture(particle1->getTexture());
	auto batchNode2 = ParticleBatchNode::createWithTexture(particle3->getTexture());

	batchNode1->addChild(particle1);
	batchNode1->addChild(particle2);
	batchNode2->addChild(particle3);

	this->addChild(batchNode1);
	this->addChild(batchNode2);

	if (!SpriteFrameCache::getInstance()->isSpriteFramesWithFileLoaded(TOLLGATE_MAP_RES_PLIST))
	{
		//SpriteFrameCache::getInstance()->addSpriteFramesWithFile(TOLLGATE_MAP_RES_PLIST, TOLLGATE_MAP_RES_PICTURE);
	}
	
	return true;
}

void StartScene::setControllerInBgLayer()
{
	/* 调用父类方法 */
	BaseScene::setControllerInBgLayer();

	/* 获取控件 */
	startGameBtn = dynamic_cast<Button*>(bgLayer->getChildByName(START_SCENE_START_GAME_BTN));
	helpBtn = dynamic_cast<Button*>(bgLayer->getChildByName(START_SCENE_HELP_BTN));
	settingBtn = dynamic_cast<Button*>(bgLayer->getChildByName(START_SCENE_SETTING_BTN));

	/* 设置监听 */
	startGameBtn->addTouchEventListener([&](Ref*, Widget::TouchEventType type) {

		/* 播放音效 */
		if (type == Widget::TouchEventType::BEGAN)
		{
			if (Effect_State)
			{
				PLAY_EFFECT(PATH_BUTTON_SOUND, false);
			}
			
			startGameBtn->runAction(ScaleTo::create(0.1f, 1.1f));
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			startGameBtn->runAction(ScaleTo::create(0.1f, 1.0f));
			this->runAction(DelayTime::create(0.1f));

			/* 跳到选关场景 */
			SceneManager::getInstance()->changeCurSceneType(SceneType::en_Select_Tollgate_Scene);
		}
		
	});

	helpBtn->addTouchEventListener([&](Ref*, Widget::TouchEventType type) {

		/* 播放音效 */
		if (type == Widget::TouchEventType::BEGAN)
		{
			if (Effect_State)
			{
				PLAY_EFFECT(PATH_BUTTON_SOUND, false);
			}
			helpBtn->runAction(ScaleTo::create(0.1f, 1.1f));
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			/* 弹出帮助层 */
			helpBtn->runAction(ScaleTo::create(0.1f, 1.0f));
			auto layer = HelpLayer::create();
			layer->setTextByCsv(PATH_I18N_PUBLIC, en_StrKey_Public_Help);
			this->addChild(layer,2);
		}

	});

	settingBtn->addTouchEventListener([&](Ref*, Widget::TouchEventType type) {

		/* 播放音效 */
		if (type == Widget::TouchEventType::BEGAN)
		{
			if (Effect_State)
			{
				PLAY_EFFECT(PATH_BUTTON_SOUND, false);
			}
			settingBtn->runAction(ScaleTo::create(0.1f, 1.1f));
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			/* 弹出设置层 */
			settingBtn->runAction(ScaleTo::create(0.1f, 1.0f));
			auto layer = SettingLayer::create();
			this->addChild(layer);
			this->addChild(layer->getBgLayer(), 2);
		}

	});
}
