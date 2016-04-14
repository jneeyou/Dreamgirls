#pragma once
#ifndef __START_ANIMATION_SCENE_H__
#define __START_ANIMATION_SCENE_H__

#include "BaseScene.h"

/*************************************************** 开始动画场景 *******************************************/

class StartAnimationScene : public BaseScene
{
public:
	CREATE_FUNC_0(StartAnimationScene, const char);
	CREATE_SCENE_0(StartAnimationScene, const char);

	virtual bool init(const char* filePath) override;

protected:
	virtual void setControllerInBgLayer()override;
};

#endif // !__START_ANIMATION_SCENE_H__
