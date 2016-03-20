#include "BaseScene.h"

BaseScene::BaseScene()
{
	bgLayer = nullptr;
	
}

BaseScene::~BaseScene()
{
	/* ȡ��������Ϣ���� */
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
	/* ����csb�����ļ� */
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

	/* ���ÿؼ� */
}