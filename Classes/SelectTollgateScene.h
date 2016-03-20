#pragma once
#ifndef __SELECT_TOLLGATE_SCENE_H__
#define __SELECT_TOLLGATE_SCENE_H__

#include "BaseScene.h"

/*************************************************** Ñ¡¹Ø³¡¾° *******************************************/

class SelectTollgateScene : public BaseScene
{
public:
	CREATE_FUNC_0(SelectTollgateScene, const char);
	CREATE_SCENE_0(SelectTollgateScene, const char);

	virtual bool init(const char* filePath) override;
};

#endif // !__SELECT_TOLLGATE_SCENE_H__
