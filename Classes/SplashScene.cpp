#include "SplashScene.h"
#include "SceneManager.h"


bool SplashScene::init(const char * filePath)
{
	if (!BaseScene::init(filePath))
	{
		return false;
	}

	m_iNumOfLoad = 0;

	/* --- ��Դ���뼰������ݳ�ʼ�� --- */

	/* �������� */
	_loadingAudioThread = new std::thread(&SplashScene::loadAudioResFiles, this);

	/* ����ͼƬ */
	loadPictureResFiles();
	
	/* ��һ�γ�ʼ���û����� */
	if (!getBoolFromXML(USER_FIRST_ENTER,false))
	{
		initUserData();
	}

	return true;
}

void SplashScene::loadPictureResFiles()
{
	// �첽����ͼƬ
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
	/* ����ͼƬ����˳�򣬼�����Ӧplist�ļ� */
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
	/* �ϲ��߳� */
	_loadingAudioThread->join();

	CC_SAFE_DELETE(_loadingAudioThread);

	/* �����¿�ʼ����*/
	SceneManager::getInstance()->changeCurSceneType(SceneType::en_Start_Scene);
}
