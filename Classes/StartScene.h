#pragma once
#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "BaseScene.h"


/********************************************************* ¿ªÊ¼³¡¾° **************************************************/

class StartScene : public BaseScene
{
public:
	StartScene();
	~StartScene();

	virtual bool init(const char* filePath) override;

	CREATE_FUNC_0(StartScene,const char);
	CREATE_SCENE_0(StartScene,const char);

protected:
	virtual void setControllerInBgLayer() override;

};

#endif // !__START_SCENE_H__
