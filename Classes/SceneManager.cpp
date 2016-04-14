#include "SceneManager.h"
#include "SplashScene.h"
#include "StartAnimationScene.h"
#include "StartScene.h"
#include "SelectTollgateScene.h"
#include "TollgateScene.h"


SceneManager* SceneManager::m_sceneManager = nullptr;


SceneManager::SceneManager()
{
	m_curSceneType = SceneType::en_None;
}

SceneManager::~SceneManager()
{
	if (m_sceneManager)
	{
		m_sceneManager->release();
	}
}

bool SceneManager::init()
{
	return true;
}

void SceneManager::changeCurSceneType(SceneType type)
{
	if (type == SceneType::en_None)
	{
		return;
	}

	/* 切换场景 */
	switchScene(type);

	/* 释放资源 */
	releaseRes(type);

	this->setCurSceneType(type);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	log(TextureCache::getInstance()->getCachedTextureInfo().c_str());
#endif
	
}


void SceneManager::switchScene(SceneType type)
{
	Scene* scene = nullptr;

	switch (type)
	{
	case SceneType::en_Splash_Scene:
		scene = SplashScene::createScene(SPLASH_SCENE_CSB_FILE);
		break;

	case SceneType::en_Select_Tollgate_Scene:
		scene = TransitionFade::create(2.0f, SelectTollgateScene::createScene(SELECT_TOLLGATE_SCENE_CSB_FILE));
		break;

	case SceneType::en_Start_Animation_Scene:
		scene = TransitionFade::create(2.0f, StartAnimationScene::createScene(START_ANIMATION_SCENE_CSB_FILE));
		break;

	case SceneType::en_Tollgate_Scene:
		scene = TransitionFade::create(2.0f, TollgateScene::createScene(TOLLGATE_SCENE_CSB_FILE));
		break;

	case SceneType::en_Start_Scene:
		scene = TransitionFade::create(2.0f, StartScene::createScene(START_SCENE_CSB_FILE));
		break;

	default:
		return;
	}

	if (!scene)
	{
		return;
	}
	
	if (DIRECTOR->getRunningScene() != nullptr)
	{
		DIRECTOR->replaceScene(scene);
	}
	else
	{
		DIRECTOR->runWithScene(scene);
	}
}

void SceneManager::releaseRes(const SceneType& type)
{
	switch (m_curSceneType)
	{
	case SceneType::en_Splash_Scene:
		SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(SPLASH_SCENE_RES_PLIST);
		TextureCache::getInstance()->removeTextureForKey(SPLASH_SCENE_RES_PICTURE);
		if (getBoolFromXML(USER_FIRST_ENTER,true))
		{
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(STARTE_ANIM_RES_PLIST, STARTE_ANIM_RES_PICTURE);
		}
		break;
	case SceneType::en_Start_Scene:
		SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(START_SCENE_RES_PLIST);
		TextureCache::getInstance()->removeTextureForKey(START_SCENE_RES_PICTURE);
		break;
	case SceneType::en_Tollgate_Scene:
		SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
		TextureCache::getInstance()->removeUnusedTextures();
		break;
	case SceneType::en_Select_Tollgate_Scene:
		SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(TOLLGATE_MAP_RES_PLIST);
		TextureCache::getInstance()->removeTextureForKey(TOLLGATE_MAP_RES_PICTURE);
		TextureCache::getInstance()->removeUnusedTextures();
		break;
	case SceneType::en_Start_Animation_Scene:
		SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(STARTE_ANIM_RES_PLIST);
		TextureCache::getInstance()->removeTextureForKey(STARTE_ANIM_RES_PICTURE);
		break;
	default:
		break;
	}
}
