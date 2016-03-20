#pragma once
#ifndef __TOLLGATE_SCENE_H__
#define __TOLLGATE_SCENE_H__

#include "BaseScene.h"

/*************************************************** ¹Ø¿¨³¡¾° *******************************************/

class TollgateScene : public BaseScene
{
public:
	CREATE_FUNC_0(TollgateScene, const char);
	CREATE_SCENE_0(TollgateScene, const char);

	virtual bool init(const char* filePath) override;
};

#endif // !__TOLLGATE_SCENE_H__
