#pragma once
#ifndef __GLOBAL_DEFINE_H__
#define __GLOBAL_DEFINE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;


/* ------------------------------------------ �꺯�� -------------------------------------- */

/* ��������setter��getter��bool���� */
#define CC_CC_SYNTHESIZE_BOOL(varName, funName)\
protected: bool varName;\
public: bool is##funName(void) const{ return varName; }\
public: void set##funName(bool var) { varName = var; }


/* ��һ��������̬create���� */
#define CREATE_FUNC_0(_TYPE_, _VAR_)	static _TYPE_* create(_VAR_* var) {\
	_TYPE_* pRet = new (std::nothrow)_TYPE_(); \
	if (pRet && pRet->init(var)) {\
		pRet->autorelease();\
	}\
	else {\
		if (pRet != nullptr) {\
			delete pRet;\
		}\
		pRet = nullptr;\
	}\
	return pRet;\
}


/* ������������ */
#define CREATE_SCENE(_TYPE_)	static Scene* createScene() {\
	auto scene = Scene::create();\
	auto layer = _TYPE_::create();\
	scene->addChild(layer);\
	return scene;\
}

/* ��һ���������������� */
#define CREATE_SCENE_0(_TYPE_,_VAR_)	static Scene* createScene(_VAR_* var ) {\
	auto scene = Scene::create();\
	auto layer = _TYPE_::create(var);\
	scene->addChild(layer);\
	return scene;\
}


/* ������������ */
#define CREATE_INSTANCE(_TYPE_,_INSTANCE_NAME_)	\
private: static _TYPE_* _INSTANCE_NAME_;\
public: static _TYPE_* getInstance() {\
	if (!_INSTANCE_NAME_) {\
		_INSTANCE_NAME_ = new (std::nothrow)_TYPE_();\
		if (_INSTANCE_NAME_ && _INSTANCE_NAME_->init()) {\
			_INSTANCE_NAME_->autorelease();\
			_INSTANCE_NAME_->retain();\
		} else {\
		CC_SAFE_DELETE(_INSTANCE_NAME_);\
		}\
	}\
	return _INSTANCE_NAME_;\
}



/* ------------------------------------------- ���滻 ------------------------------------- */
/* ��Ϣ�ɷ�ʵ�� */
#define NOTIFY	cocos2d::NotificationCenter::getInstance()


/* ����ʵ�� */
#define DIRECTOR	cocos2d::Director::getInstance()

/* �첽ͼƬ��Դ���� */
#define LOAD_IMAGE_ASYNC(filePath,callFunc)	cocos2d::Director::getInstance()->getTextureCache()->addImageAsync(filePath,CC_CALLBACK_1(callFunc,this))

/* ���ڳߴ� */
#define WINSIZE	cocos2d::Director::getInstance()->getVisibleSize()

/* �û�Ĭ��ʵ�� */
#define USERDEFAULT	cocos2d::UserDefault::getInstance()

/* ����ʵ�� */
#define AUDIOENGINE	CocosDenshion::SimpleAudioEngine::getInstance()



/* --------------------------------- �����ļ� ------------------------------------------------ */

/* ���������ļ� */
#define PLAY_MUSIC(filePath, isLoop)	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(filePath, isLoop)

/* ������Ч�ļ� */
#define PLAY_EFFECT(filePath, isLoop)	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(filePath, isLoop)

#define SOUND_EFFECT_KEY	"soundKey"			// ��Ч���
#define BGM_KEY		"bgmKey"					// �������ֱ��

#define  SOUND_EFFECT_VOL	"soundEffectVol"	//��Ч��С
#define BGM_VOL		"bgmVol"					// �������ִ�С



/* ----------------------------------- ��ȡ���� ------------------------------------------------ */

/* �������� */
#define setBoolToXML(key,value) UserDefault::getInstance()->setBoolForKey(key,value)
#define setFloatToXML(key,value) UserDefault::getInstance()->setFloatForKey(key,value)

/* ��ȡ���� */
#define getBoolFromXML(key,value) UserDefault::getInstance()->getBoolForKey(key, value)
#define getFloatFromXML(key,value) UserDefault::getInstance()->getFloatForKey(key,value)


/* ---------------------------------- �û���Ϣ ----------------------------------------------- */

#define USER_NAME	"username"
#define USER_PWD	"userpwd"
#define USER_SCORE	"userscore"

#define USER_FIRST_ENTER	"userFirstEnter"	//�û���һ�ν���


/* --------------------------------- �ļ�·�� ------------------------------------------------*/

/* ȫ�ֹ����ַ��ļ� */
#define PATH_I18N_PUBLIC	"i18n/public.csv"

/* ����򱳾� */
#define PATH_SPRITE_TEXTFIELD_BG "sprite/register.png"

/* ��걳�� */
#define PATH_SPRITE_CURSOR_BG	"cursorBg.png"

/* ע��򱳾� */
#define  PATH_SPRITE_SIGNUP_BOX_BG	"sprite/signUpBtnBg.png"

/* ��ѡ��ť���� */
#define  RADIO_BTN_CHECK	"sprite/Read_ChaeckBox.png"
#define  RADIO_BTN_NORMAL	"sprite/Read_CheckBoxBg.png"



/* ----------------------------------- csb�����ļ��� ---------------------------------------- */

#define SPLASH_SCENE_CSB_FILE						"SplashScene.csb"
#define START_SCENE_CSB_FILE						"StartScene.csb"
#define TOLLGATE_SCENE_CSB_FILE						"TollgateScene.csb"
#define START_ANIMATION_SCENE_CSB_FILE				"StartAnimationScene.csb"
#define SELECT_TOLLGATE_SCENE_CSB_FILE				"SelectTollgateScene.csb"



/* ---------------------------------- �����ؼ��� -------------------------------------------- */

/* ��ʼ���� */
#define START_SCENE_START_GAME_BTN		"startGameBtn"
#define START_SCENE_HELP_BTN			"helpBtn"
#define START_SCENE_SETTING_BTN			"settingBtn"

/* �ؿ����� */



/* -------------------------------------------- ��Ϣ���� ---------------------------------- */

#define USER_LOGIN_MSG			"UserLoginMsg"
#define USER_SIGNUP_MSG			"UserSignUpMsg"
#define USER_SMS_CHECK_MSG		"UserSmsCheckMsg"
#define USER_EMAIL_CHECK_MSG	"UserSmsCheckMsg"

#define USER_LOGIN_FAILED		"UserLoginFailed"
#define USER_SIGNUP_FAILED		"signUpFailed"
#define USER_SMS_CHECK_FAILED	"UserSmsCheckFailed"
#define USER_EMAIL_CHECK_FAILED	"UserSmsCheckFailed"


#define TAG_READ_LAYER	1
#define TAG_PLAY_GAME_LAYER	2
#define TAG_CHAT_LAYER	3

#endif // !__GLOBAL_DEFINE_H__
