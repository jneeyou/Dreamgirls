#include "StartAnimationScene.h"

bool StartAnimationScene::init(const char * filePath)
{
	if (!BaseScene::init(filePath))
	{
		return false;
	}

	return true;
}
