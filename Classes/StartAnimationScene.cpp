#include "StartAnimationScene.h"
#include "SceneManager.h"


bool StartAnimationScene::init(const char * filePath)
{
	if (!BaseScene::init(filePath))
	{
		return false;
	}

	/* 播放音乐 */
	PLAY_MUSIC(PATH_ST_ANIM_SOUND, false);

	return true;
}

void StartAnimationScene::setControllerInBgLayer()
{
	/* 添加下雨粒子 */
	auto rain = ParticleSystemQuad::create("yu.plist");
	rain->setPosition(ccp(WINSIZE.width / 2, WINSIZE.height));
	//rain->setSpeed(50);

	auto batchNode = ParticleBatchNode::createWithTexture(rain->getTexture());
	batchNode->addChild(rain);
	bgLayer->addChild(batchNode);

	/* 播放动画 */
	auto timeline = CSLoader::createTimeline(START_ANIMATION_SCENE_CSB_FILE);
	timeline->setTag(1);

	auto anim = timeline->getAnimationInfo("anim");
	anim.clipEndCallBack = [&]() {
		auto colorLayer = LayerColor::create(Color4B(255, 255, 255,0));
		auto in = FadeIn::create(1.0f);
		auto call1 = CallFunc::create([&]() {
			this->removeChild(bgLayer,true);

			auto particle = ParticleSystemQuad::create("chuanyue.plist");
			this->addChild(particle);
			auto fade =  FadeIn::create(1.0f);
			particle->runAction(fade);
			particle->setPosition(ccp(WINSIZE.width / 2, WINSIZE.height / 2));

		});
		auto out = FadeOut::create(1.0f);
		auto call2 = CallFunc::create([&](){
			/* 跳到关卡场景 */
			SceneManager::getInstance()->changeCurSceneType(SceneType::en_Tollgate_Scene);
		});
		colorLayer->runAction(Sequence::create(in, call1, out,call2, nullptr));
		this->addChild(colorLayer);
	};
	timeline->removeAnimationInfo("anim");
	timeline->addAnimationInfo(anim);

	timeline->play("anim", false);
	bgLayer->runAction(timeline);
}
