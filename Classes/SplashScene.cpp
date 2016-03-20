#include "SplashScene.h"
#include "SceneManager.h"



bool SplashScene::init(const char * filePath)
{
	if (!BaseScene::init(filePath))
	{
		return false;
	}

	m_iNumOfLoad = 0;

	/* --- 资源载入及相关数据初始化 --- */

	/* 加载音乐 */
	_loadingAudioThread = new std::thread(&SplashScene::loadAudioResFiles, this);

	/* 加载图片 */
	loadPictureResFiles();
	
	/* 第一次初始化用户数据 */
	if (!getBoolFromXML(USER_FIRST_ENTER,false))
	{
		initUserData();
	}

	return true;
}

void SplashScene::loadPictureResFiles()
{
	
	LOAD_IMAGE_ASYNC("", SplashScene::imageLoadCallFunc);
}

void SplashScene::loadAudioResFiles()
{
	AUDIOENGINE->preloadBackgroundMusic("");
}

void SplashScene::initUserData()
{

}

void SplashScene::imageLoadCallFunc(Texture2D * texture)
{
	switch (m_iNumOfLoad++)
	{
	case 0:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/startGame.plist", texture);
		this->scheduleOnce(schedule_selector(SplashScene::gotoNextScene),1.0f);
	default:
		break;
	}
}

void SplashScene::gotoNextScene(float dt)
{
	/* 合并线程 */
	_loadingAudioThread->join();

	CC_SAFE_DELETE(_loadingAudioThread);

	/* 跳到下开始场景*/
	SceneManager::getInstance()->changeCurSceneType(SceneType::en_Start_Scene);
}
