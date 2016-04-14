#pragma once
#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "BaseScene.h"

/*************************************************** ���ɳ��� *******************************************/

class SplashScene : public BaseScene
{
public:
	CREATE_FUNC_0(SplashScene, const char);
	CREATE_SCENE_0(SplashScene, const char);

	virtual bool init(const char* filePath) override;

protected:
	/* ����ͼƬ��Դ�ļ� */
	virtual void loadPictureResFiles(float dt);

	/* ����������Դ�ļ� */
	virtual void loadAudioResFiles();

	/* ��ʼ���û����� */
	virtual void initUserData();

	/* ͼƬ���ػص����� */
	void imageLoadCallFunc(Texture2D* texture);

	/* ������һ������ */
	void gotoNextScene(float dt);

private:
	/* ���ּ����߳� */
	std::thread* _loadingAudioThread ;

	/* ������Դ���� */
	int m_iNumOfLoad;

	/* �����Ƿ���� */
	bool m_isActionDone;

	/* ��Դ�Ƿ������� */
	bool m_isResLoaded;
};

#endif // !__SPLASH_SCENE_H__
