#pragma once
#ifndef __TOOLGATE_SPLASH_SCENE_H__
#define __TOOLGATE_SPLASH_SCENE_H__

#include "BaseScene.h"

/*************************************************** �ؿ����ɳ��� *******************************************/

class TollgateSplashScene : public BaseScene
{
public:
	CREATE_FUNC_0(TollgateSplashScene, const char);
	CREATE_SCENE_0(TollgateSplashScene, const char);

	virtual bool init(const char* filePath) override;
};

#endif // !__TOOLGATE_SPLASH_SCENE_H__
