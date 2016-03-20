#include "StartScene.h"
#include "SceneManager.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::init(const char* filePath)
{
	if (!BaseScene::init(filePath))
	{
		return false;
	}


	return true;
}

void StartScene::setControllerInBgLayer()
{
	/* 调用父类方法 */
	BaseScene::setControllerInBgLayer();

	/* 获取控件 */
	auto startGameBtn = dynamic_cast<Button*>(bgLayer->getChildByName(START_SCENE_START_GAME_BTN));
	auto helpBtn = dynamic_cast<Button*>(bgLayer->getChildByName(START_SCENE_HELP_BTN));
	auto settingBtn = dynamic_cast<Button*>(bgLayer->getChildByName(START_SCENE_SETTING_BTN));

	/* 设置监听 */
	startGameBtn->addTouchEventListener([](Ref*, Widget::TouchEventType type) {

		/* 播放音效 */
		if (type == Widget::TouchEventType::BEGAN)
		{

		}

		if (type == Widget::TouchEventType::ENDED)
		{
			/* 第一次进入跳到开始动画场景，否则跳到关卡场景 */
			bool ret = getBoolFromXML(USER_FIRST_ENTER, false);

			if (!ret)	//第一次进入
			{
				setBoolToXML(USER_FIRST_ENTER, true);
				USERDEFAULT->flush();

				SceneManager::getInstance()->changeCurSceneType(SceneType::en_Start_Animation_Scene);
			}
			else		//非第一次
			{
				SceneManager::getInstance()->changeCurSceneType(SceneType::en_Tollgate_Scene);
			}
		}
		
	});

	helpBtn->addTouchEventListener([](Ref*, Widget::TouchEventType type) {

		/* 播放音效 */
		if (type == Widget::TouchEventType::BEGAN)
		{

		}

		if (type == Widget::TouchEventType::ENDED)
		{
			/* 弹出帮助层 */
		}

	});

	settingBtn->addTouchEventListener([](Ref*, Widget::TouchEventType type) {

		/* 播放音效 */
		if (type == Widget::TouchEventType::BEGAN)
		{

		}

		if (type == Widget::TouchEventType::ENDED)
		{
			/* 弹出设置层 */
		}

	});
}
