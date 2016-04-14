#include "TollgateSplashLayer.h"
#include "GlobalDefine.h"


TollgateSplashLayer::TollgateSplashLayer()
{
}

TollgateSplashLayer::~TollgateSplashLayer()
{
	NOTIFY->removeAllObservers(this);
}

bool TollgateSplashLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}


	return true;
}
