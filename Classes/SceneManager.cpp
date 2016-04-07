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
	this->setCurSceneType(type);

	if (m_curSceneType == SceneType::en_None)
	{
		return;
	}

	/* ÇÐ»»³¡¾° */
	switchScene();
}

void SceneManager::switchScene()
{
	Scene* scene = nullptr;

	switch (m_curSceneType)
	{
	case SceneType::en_Splash_Scene:
		scene = SplashScene::createScene(SPLASH_SCENE_CSB_FILE);
		break;

	case SceneType::en_Select_Tollgate_Scene:
		scene = TransitionFade::create(1.0f, SelectTollgateScene::createScene(SELECT_TOLLGATE_SCENE_CSB_FILE));
		break;

	case SceneType::en_Start_Animation_Scene:
		scene = StartAnimationScene::createScene(START_ANIMATION_SCENE_CSB_FILE);
		break;

	case SceneType::en_Tollgate_Scene:
		scene = TransitionFade::create(1.0f, TollgateScene::createScene(TOLLGATE_SCENE_CSB_FILE));
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
