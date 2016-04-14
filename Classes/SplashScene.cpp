#include "SplashScene.h"
#include "SceneManager.h"


bool SplashScene::init(const char * filePath)
{
	if (!BaseScene::init(filePath))
	{
		return false;
	}

	m_iNumOfLoad = 0;
	m_isActionDone = false;
	m_isResLoaded = false;

	/* --- ��Դ���뼰������ݳ�ʼ�� --- */

	/* �������� */
	_loadingAudioThread = new std::thread(&SplashScene::loadAudioResFiles, this);

	/* ��������������ͼƬ */
	this->scheduleOnce(schedule_selector(SplashScene::loadPictureResFiles), 0.2f);
	
	/* ��һ�γ�ʼ���û����� */
	if (!getBoolFromXML(USER_FIRST_ENTER,false))
	{
		initUserData();
	}

	/* ���ų������� */
	auto timeline = CSLoader::createTimeline(SPLASH_SCENE_CSB_FILE);

	auto anim = timeline->getAnimationInfo("splash");
	anim.clipEndCallBack = [&](void) {
		m_isActionDone = true;
		gotoNextScene(0.1f);
	};
	timeline->removeAnimationInfo("splash");
	timeline->addAnimationInfo(anim);

	timeline->play("splash", false);
	bgLayer->runAction(timeline);
	timeline->gotoFrameAndPause(0);

	timeline->play("splash", false);

	return true;
}

void SplashScene::loadPictureResFiles(float dt)
{
	// �첽����ͼƬ
	LOAD_IMAGE_ASYNC(TOLLGATE_MAP_RES_PICTURE, SplashScene::imageLoadCallFunc);

}

void SplashScene::loadAudioResFiles()
{
	if (!getBoolFromXML(USER_FIRST_ENTER,true))
	{
		AUDIOENGINE->preloadBackgroundMusic(PATH_BGM_SOUND);
	}
	else
	{
		AUDIOENGINE->preloadBackgroundMusic(PATH_ST_ANIM_SOUND);
	}
}

void SplashScene::initUserData()
{
	setIntToXML(CURRENT_TOLLGATE, 2);
	setIntToXML(MAX_TOLLGATE_NUM, 10);
	setIntToXML(UNLOCK_TOLLGATE_NUM, 5);

	USERDEFAULT->flush();
}

void SplashScene::imageLoadCallFunc(Texture2D * texture)
{
	log("count:%d",m_iNumOfLoad);

	/* ����ͼƬ����˳�򣬼�����Ӧplist�ļ� */
	switch (m_iNumOfLoad++)
	{
	case 0:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(TOLLGATE_MAP_RES_PLIST, texture);
		LOAD_IMAGE_ASYNC(START_SCENE_RES_PICTURE, SplashScene::imageLoadCallFunc);
		break;
	case 1:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(START_SCENE_RES_PLIST, texture);
		LOAD_IMAGE_ASYNC(TOLLGATE_SCENE_RES_PICTURE, SplashScene::imageLoadCallFunc);
		break;
	case 2:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(TOLLGATE_SCENE_RES_PLIST, texture);
		LOAD_IMAGE_ASYNC(SLT_TOLLGATE_SCENE_RES_PICTURE, SplashScene::imageLoadCallFunc);
		break;
	case 3:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(SLT_TOLLGATE_SCENE_RES_PLIST, texture);
		LOAD_IMAGE_ASYNC(POP_LAYER_RES_PICTURE, SplashScene::imageLoadCallFunc);
		break;
	case 4:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(POP_LAYER_RES_PLIST, texture);
		LOAD_IMAGE_ASYNC(GIRL_RES_PICTURE, SplashScene::imageLoadCallFunc);
		break;
	case 5:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(GIRL_RES_PLIST, texture);
		m_isResLoaded = true;
		this->scheduleOnce(schedule_selector(SplashScene::gotoNextScene), 0.1f);
		break;
	default:
		break;
	}
}

void SplashScene::gotoNextScene(float dt)
{
	if (!m_isActionDone || !m_isResLoaded)
	{
		return;
	}

	/* �ϲ��߳� */
	_loadingAudioThread->join();

	CC_SAFE_DELETE(_loadingAudioThread);

	/* ��һ�ν���������ʼ�������������������ؿ����� */
	bool ret = getBoolFromXML(USER_FIRST_ENTER, true);
	if (ret)	//��һ�ν���
	{
		SceneManager::getInstance()->changeCurSceneType(SceneType::en_Start_Animation_Scene);
	}
	else		//�ǵ�һ��, ������ʼ����
	{
		SceneManager::getInstance()->changeCurSceneType(SceneType::en_Start_Scene);
	}
}

