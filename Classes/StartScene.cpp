#include "StartScene.h"
#include "SceneManager.h"
#include "GlobalDefine.h"


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

	/* �������� */
	PLAY_MUSIC(PATH_BGM_SOUND, true);


	return true;
}

void StartScene::setControllerInBgLayer()
{
	/* ���ø��෽�� */
	BaseScene::setControllerInBgLayer();

	/* ��ȡ�ؼ� */
	startGameBtn = dynamic_cast<Button*>(bgLayer->getChildByName(START_SCENE_START_GAME_BTN));
	helpBtn = dynamic_cast<Button*>(bgLayer->getChildByName(START_SCENE_HELP_BTN));
	settingBtn = dynamic_cast<Button*>(bgLayer->getChildByName(START_SCENE_SETTING_BTN));

	/* ���ü��� */
	startGameBtn->addTouchEventListener([&](Ref*, Widget::TouchEventType type) {

		/* ������Ч */
		if (type == Widget::TouchEventType::BEGAN)
		{
			PLAY_EFFECT(PATH_BUTTON_SOUND, false);
			startGameBtn->runAction(ScaleTo::create(0.1f, 1.1f));
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			/* ��һ�ν���������ʼ�������������������ؿ����� */
			bool ret = getBoolFromXML(USER_FIRST_ENTER, false);
			startGameBtn->runAction(ScaleTo::create(0.1f, 1.0f));
			this->runAction(DelayTime::create(0.1f));

			if (!ret)	//��һ�ν���
			{
				setBoolToXML(USER_FIRST_ENTER, true);
				USERDEFAULT->flush();

				SceneManager::getInstance()->changeCurSceneType(SceneType::en_Start_Animation_Scene);
			}
			else		//�ǵ�һ��
			{
				SceneManager::getInstance()->changeCurSceneType(SceneType::en_Select_Tollgate_Scene);
			}
		}
		
	});

	helpBtn->addTouchEventListener([&](Ref*, Widget::TouchEventType type) {

		/* ������Ч */
		if (type == Widget::TouchEventType::BEGAN)
		{
			PLAY_EFFECT(PATH_BUTTON_SOUND, false);
			helpBtn->runAction(ScaleTo::create(0.1f, 1.1f));
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			/* ���������� */
			helpBtn->runAction(ScaleTo::create(0.1f, 1.0f));
		}

	});

	settingBtn->addTouchEventListener([&](Ref*, Widget::TouchEventType type) {

		/* ������Ч */
		if (type == Widget::TouchEventType::BEGAN)
		{
			PLAY_EFFECT(PATH_BUTTON_SOUND, false);
			settingBtn->runAction(ScaleTo::create(0.1f, 1.1f));
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			/* �������ò� */
			settingBtn->runAction(ScaleTo::create(0.1f, 1.0f));
		}

	});
}
