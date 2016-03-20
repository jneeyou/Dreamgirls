#include "BaseScene.h"

BaseScene::BaseScene()
{
	bgLayer = nullptr;
	
}

BaseScene::~BaseScene()
{
	/* 取消所有消息服务 */
	NotificationCenter::getInstance()->removeAllObservers(this);
}


bool BaseScene::init()
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!Layer::init());
		bRet = true;

	} while (0);

	return bRet;
}

bool BaseScene::init(const char * filePath)
{
	if (!init())
	{
		return false;
	}

	setBgLayerByFile(filePath);

	return true;
}

void BaseScene::setBgLayerByFile(const char * filePath)
{
	/* 加载csb场景文件 */
	bgLayer = CSLoader::createNode(filePath);
	if (bgLayer)
	{
		this->addChild(bgLayer);
	}

	setControllerInBgLayer();
}


void BaseScene::setControllerInBgLayer()
{
	if (bgLayer)
	{
		return;
	}

	/* 设置控件 */
}