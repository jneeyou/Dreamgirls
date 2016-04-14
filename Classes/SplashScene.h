#pragma once
#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "BaseScene.h"

/*************************************************** 过渡场景 *******************************************/

class SplashScene : public BaseScene
{
public:
	CREATE_FUNC_0(SplashScene, const char);
	CREATE_SCENE_0(SplashScene, const char);

	virtual bool init(const char* filePath) override;

protected:
	/* 加载图片资源文件 */
	virtual void loadPictureResFiles(float dt);

	/* 加载音乐资源文件 */
	virtual void loadAudioResFiles();

	/* 初始化用户数据 */
	virtual void initUserData();

	/* 图片加载回调函数 */
	void imageLoadCallFunc(Texture2D* texture);

	/* 进入下一个场景 */
	void gotoNextScene(float dt);

private:
	/* 音乐加载线程 */
	std::thread* _loadingAudioThread ;

	/* 加载资源计数 */
	int m_iNumOfLoad;

	/* 动画是否结束 */
	bool m_isActionDone;

	/* 资源是否加载完成 */
	bool m_isResLoaded;
};

#endif // !__SPLASH_SCENE_H__
