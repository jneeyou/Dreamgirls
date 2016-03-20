#pragma once
#ifndef __GLOBAL_DEFINE_H__
#define __GLOBAL_DEFINE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;


/* ------------------------------------------ 宏函数 -------------------------------------- */

/* 创建包括setter，getter的bool变量 */
#define CC_CC_SYNTHESIZE_BOOL(varName, funName)\
protected: bool varName;\
public: bool is##funName(void) const{ return varName; }\
public: void set##funName(bool var) { varName = var; }


/* 带一个参数静态create方法 */
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


/* 创建场景方法 */
#define CREATE_SCENE(_TYPE_)	static Scene* createScene() {\
	auto scene = Scene::create();\
	auto layer = _TYPE_::create();\
	scene->addChild(layer);\
	return scene;\
}

/* 带一参数创建场景方法 */
#define CREATE_SCENE_0(_TYPE_,_VAR_)	static Scene* createScene(_VAR_* var ) {\
	auto scene = Scene::create();\
	auto layer = _TYPE_::create(var);\
	scene->addChild(layer);\
	return scene;\
}


/* 创景单例对象 */
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



/* ------------------------------------------- 宏替换 ------------------------------------- */
/* 消息派发实例 */
#define NOTIFY	cocos2d::NotificationCenter::getInstance()


/* 导演实例 */
#define DIRECTOR	cocos2d::Director::getInstance()

/* 异步图片资源加载 */
#define LOAD_IMAGE_ASYNC(filePath,callFunc)	cocos2d::Director::getInstance()->getTextureCache()->addImageAsync(filePath,CC_CALLBACK_1(callFunc,this))

/* 窗口尺寸 */
#define WINSIZE	cocos2d::Director::getInstance()->getVisibleSize()

/* 用户默认实例 */
#define USERDEFAULT	cocos2d::UserDefault::getInstance()

/* 音乐实例 */
#define AUDIOENGINE	CocosDenshion::SimpleAudioEngine::getInstance()



/* --------------------------------- 音乐文件 ------------------------------------------------ */

/* 播放音乐文件 */
#define PLAY_MUSIC(filePath, isLoop)	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(filePath, isLoop)

/* 播放音效文件 */
#define PLAY_EFFECT(filePath, isLoop)	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(filePath, isLoop)

#define SOUND_EFFECT_KEY	"soundKey"			// 音效标记
#define BGM_KEY		"bgmKey"					// 背景音乐标记

#define  SOUND_EFFECT_VOL	"soundEffectVol"	//音效大小
#define BGM_VOL		"bgmVol"					// 背景音乐大小



/* ----------------------------------- 存取数据 ------------------------------------------------ */

/* 保存数据 */
#define setBoolToXML(key,value) UserDefault::getInstance()->setBoolForKey(key,value)
#define setFloatToXML(key,value) UserDefault::getInstance()->setFloatForKey(key,value)

/* 获取数据 */
#define getBoolFromXML(key,value) UserDefault::getInstance()->getBoolForKey(key, value)
#define getFloatFromXML(key,value) UserDefault::getInstance()->getFloatForKey(key,value)


/* ---------------------------------- 用户信息 ----------------------------------------------- */

#define USER_NAME	"username"
#define USER_PWD	"userpwd"
#define USER_SCORE	"userscore"

#define USER_FIRST_ENTER	"userFirstEnter"	//用户第一次进入


/* --------------------------------- 文件路径 ------------------------------------------------*/

/* 全局公用字符文件 */
#define PATH_I18N_PUBLIC	"i18n/public.csv"

/* 输入框背景 */
#define PATH_SPRITE_TEXTFIELD_BG "sprite/register.png"

/* 光标背景 */
#define PATH_SPRITE_CURSOR_BG	"cursorBg.png"

/* 注册框背景 */
#define  PATH_SPRITE_SIGNUP_BOX_BG	"sprite/signUpBtnBg.png"

/* 单选按钮背景 */
#define  RADIO_BTN_CHECK	"sprite/Read_ChaeckBox.png"
#define  RADIO_BTN_NORMAL	"sprite/Read_CheckBoxBg.png"



/* ----------------------------------- csb场景文件名 ---------------------------------------- */

#define SPLASH_SCENE_CSB_FILE						"SplashScene.csb"
#define START_SCENE_CSB_FILE						"StartScene.csb"
#define TOLLGATE_SCENE_CSB_FILE						"TollgateScene.csb"
#define START_ANIMATION_SCENE_CSB_FILE				"StartAnimationScene.csb"
#define SELECT_TOLLGATE_SCENE_CSB_FILE				"SelectTollgateScene.csb"



/* ---------------------------------- 场景控件名 -------------------------------------------- */

/* 开始场景 */
#define START_SCENE_START_GAME_BTN		"startGameBtn"
#define START_SCENE_HELP_BTN			"helpBtn"
#define START_SCENE_SETTING_BTN			"settingBtn"

/* 关卡场景 */



/* -------------------------------------------- 消息定义 ---------------------------------- */

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
