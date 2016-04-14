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

/* 音乐文件路径 */
#define PATH_BGM_SOUND		    "sound/bgm.mp3"
#define PATH_BUTTON_SOUND		"sound/button.mp3"
#define PATH_JUMP_SOUND			"sound/jump.mp3"
#define PATH_RUN_SOUND			"sound/run.mp3"
#define PATH_SLID_SOUND			"sound/sliding.mp3"
#define PATH_ENTER_SOUND		"sound/enter.mp3"
#define PATH_CEASH_SOUND		"sound/crash.mp3"
#define PATH_ST_ANIM_SOUND		"sound/home.mp3"

/* ----------------------------------- 存取数据 ------------------------------------------------ */

/* 保存数据 */
#define setBoolToXML(key,value) UserDefault::getInstance()->setBoolForKey(key,value)
#define setFloatToXML(key,value) UserDefault::getInstance()->setFloatForKey(key,value)
#define setIntToXML(key,value) UserDefault::getInstance()->setIntegerForKey(key,value)

/* 获取数据 */
#define getBoolFromXML(key,value) UserDefault::getInstance()->getBoolForKey(key, value)
#define getFloatFromXML(key,value) UserDefault::getInstance()->getFloatForKey(key,value)
#define getIntFromXML(key,value) UserDefault::getInstance()->getIntegerForKey(key,value)

/* 音效状态 */
static bool Effect_State = getBoolFromXML(SOUND_EFFECT_KEY, true);

/* ---------------------------------- 用户信息 ----------------------------------------------- */

#define USER_NAME	"username"
#define USER_PWD	"userpwd"
#define USER_SCORE	"userscore"

#define USER_FIRST_ENTER	"userFirstEnter"		// 用户第一次进入
#define CURRENT_TOLLGATE	"currentTollgate"		// 当前关卡
#define MAX_TOLLGATE_NUM	"MaxTollgateNumber"		// 最大关卡数
#define UNLOCK_TOLLGATE_NUM	"UnlockTollgateNumber"	// 解锁关卡数

/* -----------------------------------文件路径 ------------------------------------------------*/

/* 全局公用字符文件 */
#define PATH_I18N_PUBLIC	"csv/public.csv"

/* 怪物配置文件 */
#define PATH_CSV_MONSTER	"csv/monster.csv"

/* 玩家配置文件 */
#define PATH_CSV_PLAYER		"csv/player.csv"

/* 输入框背景 */
#define PATH_SPRITE_TEXTFIELD_BG "sprite/register.png"

/* 光标背景 */
#define PATH_SPRITE_CURSOR_BG	"cursorBg.png"

/* 注册框背景 */
#define  PATH_SPRITE_SIGNUP_BOX_BG	"sprite/signUpBtnBg.png"

/* 单选按钮背景 */
#define  RADIO_BTN_CHECK	"sprite/Read_ChaeckBox.png"
#define  RADIO_BTN_NORMAL	"sprite/Read_CheckBoxBg.png"

/* plist 文件 */
#define TOLLGATE_MAP_RES_PLIST			"tollgate_maps.plist"
#define SLT_TOLLGATE_SCENE_RES_PLIST	"SltTollgateSceneRes.plist"
#define GIRL_RES_PLIST					"GirlResource.plist"
#define POP_LAYER_RES_PLIST				"PopLayerRes.plist"
#define TOLLGATE_SCENE_RES_PLIST		"TollgateSceneRes.plist"
#define START_SCENE_RES_PLIST		    "StartSceneRes.plist"
#define STARTE_ANIM_RES_PLIST		    "startAnimRes.plist"
#define SPLASH_SCENE_RES_PLIST			"SplashSceneRes.plist"


/*plist对应图片 */
#define TOLLGATE_MAP_RES_PICTURE		"tollgate_maps.pvr.ccz"
#define SLT_TOLLGATE_SCENE_RES_PICTURE	"SltTollgateSceneRes.png"
#define GIRL_RES_PICTURE				"GirlResource.png"
#define POP_LAYER_RES_PICTURE			"PopLayerRes.png"
#define TOLLGATE_SCENE_RES_PICTURE		"TollgateSceneRes.png"
#define START_SCENE_RES_PICTURE		    "StartSceneRes.png"
#define STARTE_ANIM_RES_PICTURE			"startAnimRes.png"
#define SPLASH_SCENE_RES_PICTURE		"SplashSceneRes.png"


/* 动画文件 */
#define PATH_PLAYER_AIMATION_FILE		"girl.csb"


/* ----------------------------------- csb场景文件名 ---------------------------------------- */

#define SPLASH_SCENE_CSB_FILE						"SplashScene.csb"
#define START_SCENE_CSB_FILE						"StartScene.csb"
#define TOLLGATE_SCENE_CSB_FILE						"TollgateScene.csb"
#define START_ANIMATION_SCENE_CSB_FILE				"StartAnimationScene.csb"
#define SELECT_TOLLGATE_SCENE_CSB_FILE				"SelectTollgateScene.csb"

#define SETTING_LAYER_CSB_FILE						"SettingLayer.csb"
#define PAUSE_LAYER_CSB_FILE						"PauseLayer.csb"
#define HELP_LAYER_CSB_FILE							"HelpLayer.csb"


/* ---------------------------------- 场景控件名 -------------------------------------------- */

/* 开始场景 */
#define START_SCENE_START_GAME_BTN		"startGameBtn"
#define START_SCENE_HELP_BTN			"helpBtn"
#define START_SCENE_SETTING_BTN			"settingBtn"

/* 关卡场景 */
#define TOLLGATE_SCENE_LOGIC_LAYER		"logicLayer"
#define TOLLGATE_SCENE_BG_LAYER		     "bgLayer"

#define TOLL_LOGIC_LAYER_RIGHT_MOVE_BTN	"rightMoveBtn"
#define TOLL_LOGIC_LAYER_JUMP_BTN		"jumpBtn"
#define TOLL_LOGIC_LAYER_PAUSE_BTN		"pauseBtn"
#define TOLL_LOGIC_LAYER_SCORE_LABEL	"scoreLabel"

#define TOLL__BG_LAYER_BG_ONE			"bg_one"
#define TOLL__BG_LAYER_BG_TWO			"bg_two"

/* -------------------------------------------- 消息定义 ---------------------------------- */

#define TAG_START_MOVE_BG_MSG			"start_move_bg"
#define TAG_STOP_MOVE_BG_MSG			"stop_move_bg"

/* -------------------------------------------- 地图资源 ---------------------------------- */
#define LV_1_RES_1						"level/lv_1_res.pvr.ccz"
#define LV_1_RES_2						"level/river.png"
#define LV_1_RES_3						"level/dd.png"
#define LV_2_RES_1						"level/roadPlist.png"
#define LV_3_RES_1						"level/road3.png"
#define LV_4_RES_1						"level/tile.png"
#define LV_5_RES_1						"level/tile.png"
#define LV_6_RES_1						"level/tile.png"
#define LV_7_RES_1						"level/tile.png"
#define LV_8_RES_1						"level/tile.png"
#define LV_9_RES_1						"level/tile.png"
#define LV_10_RES_1						"level/tile.png"

#endif // !__GLOBAL_DEFINE_H__
