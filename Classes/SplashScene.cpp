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
	// 异步加载图片
	LOAD_IMAGE_ASYNC(PATH_GIRLS_RES_PICTURE_FILE, SplashScene::imageLoadCallFunc);
}

void SplashScene::loadAudioResFiles()
{
	AUDIOENGINE->preloadBackgroundMusic(PATH_BGM_SOUND);
}

void SplashScene::initUserData()
{

}

void SplashScene::imageLoadCallFunc(Texture2D * texture)
{
	/* 根据图片载入顺序，加载相应plist文件 */
	switch (m_iNumOfLoad++)
	{
	case 0:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_GIRLS_RES_PLIST_FILE, texture);
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
