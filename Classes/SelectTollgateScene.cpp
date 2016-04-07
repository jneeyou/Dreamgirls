#include "SelectTollgateScene.h"
#include "SceneManager.h"

/* 获得当前关卡名 */
#define GetCurLevelName(m_iCurLevel)	("SltTollgateSceneRes/lv_" + Value(m_iCurLevel).asString() + ".png")


bool SelectTollgateScene::init(const char * filePath)
{
	interval_pos = 40;
	m_isSliding = false;
	m_unlockTollgateNum = getIntFromXML(UNLOCK_TOLLGATE_NUM, 5);
	m_maxTollgateNum = getIntFromXML(MAX_TOLLGATE_NUM, 10);
	m_iCurTollgate = 2;
	m_actionFlag = 0;// 0:无动作，-1：左滑，1：右滑
	m_touchTime = 0;

	if (!BaseScene::init(filePath))
	{
		return false;
	}

	/* 设置监听 */
	bindTouchListener();

	/* 只解锁了1关 */
	if (m_unlockTollgateNum == 1)
	{
		updateUI(false,0.01f);
	}

	/* 启动计时 */
	this->scheduleUpdate();

	auto sPosX = lv_center->getPositionX() - lv_center->getContentSize().width / 2 + 5;
	auto sPosY = lv_center->getPositionY() - lv_center->getContentSize().height / 2 + 5;
	auto ePosX = lv_center->getPositionX() + lv_center->getContentSize().width / 2 - 5;
	auto ePosY = lv_center->getPositionY() + lv_center->getContentSize().height / 2 - 5;

	boundBox = Rect(sPosX, sPosY, ePosX, ePosY);

	return true;
}

void SelectTollgateScene::update(float dt)
{
	if (m_isCountTime == false)
	{
		return;
	}
	m_touchTime += dt;
}

void SelectTollgateScene::setControllerInBgLayer()
{
	/* 设置关卡图片 */
	lv_center = dynamic_cast<Sprite*>(bgLayer->getChildByName("lv_center"));
	lv_right = dynamic_cast<Sprite*>(bgLayer->getChildByName("lv_right"));
	lv_left = dynamic_cast<Sprite*>(bgLayer->getChildByName("lv_left"));

	lv_center->setZOrder(2);
	lv_left->setZOrder(0);
	lv_right->setZOrder(0);

	slt_bar_yes = dynamic_cast<Sprite*>(bgLayer->getChildByName("sp_slt_bar_no"));

	auto slt_bar_no1 = dynamic_cast<Sprite*>(bgLayer->getChildByName("slt_bar_yes_1"));
	auto slt_bar_no2 = dynamic_cast<Sprite*>(bgLayer->getChildByName("slt_bar_yes_2"));

	interval_pos = slt_bar_no2->getPositionX() - slt_bar_no1->getPositionX();
	slt_bar_yes->setPositionX(slt_bar_no1->getPositionX () + (m_iCurTollgate - 1) * interval_pos);
	slt_bar_yes->setVisible(true);
	slt_bar_yes->setZOrder(6);

	/* 设置按钮监听 */
	home_btn = dynamic_cast<Button*>(bgLayer->getChildByName("home_btn"));
	setting_btn = dynamic_cast<Button*>(bgLayer->getChildByName("setting_btn"));

	home_btn->setZOrder(5);
	setting_btn->setZOrder(5);

	home_btn->addTouchEventListener([&](Ref* ref, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			PLAY_EFFECT(PATH_BUTTON_SOUND,false);
			home_btn->runAction(ScaleTo::create(0.1f, 1.1f));
			return;
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			home_btn->runAction(ScaleTo::create(0.1f, 1.0f));
			this->runAction(DelayTime::create(0.1f));
			SceneManager::getInstance()->changeCurSceneType(SceneType::en_Start_Scene);
		}
	});

	setting_btn->addTouchEventListener([&](Ref* ref, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			PLAY_EFFECT(PATH_BUTTON_SOUND, false);
			setting_btn->runAction(ScaleTo::create(0.1f, 1.1f));
			return;
		}

		if (type == Widget::TouchEventType::ENDED)
		{
			/* 弹出设置层 */
			setting_btn->runAction(ScaleTo::create(0.1f, 1.0f));
		}
	});

	/* 设置滑动球背景 */
	for (int i = 1; i <= m_unlockTollgateNum; i++)
	{
		slt_bar_no1 = (Sprite*)(bgLayer->getChildByName("slt_bar_yes_" + Value(i).asString()));
		slt_bar_no1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("SltTollgateSceneRes/slt_bar_no.png"));
		slt_bar_no1->setZOrder(5);
	}
}

void SelectTollgateScene::updateUI(bool isLeftSiding, float tm)
{
	auto div_tm = tm / 2.0f;

	/* 滑到头或尾 */
	if ((m_iCurTollgate == 1 && !isLeftSiding) ||
		(m_iCurTollgate == m_unlockTollgateNum && isLeftSiding))
	{
		auto scaleLarge = ScaleTo::create(div_tm, 1.1f);
		auto scaleSmall = ScaleTo::create(div_tm, 1.0f);
		auto calls = CallFunc::create([&]() {
			m_actionFlag = 0;
		});
		auto seqScale = Sequence::create(scaleLarge, scaleSmall, calls, nullptr);

		lv_center->runAction(seqScale);
		
		return;
	}
	

	if (isLeftSiding)
	{
		m_iCurTollgate++;

		/* 左关卡图移动动作 */
		auto leftMove = MoveBy::create(div_tm, Vec2(-lv_left->getPositionX() - lv_left->getContentSize().width / 2, 0));
		auto call = CallFunc::create([&]() {
			lv_left->setPositionX(WINSIZE.width + lv_left->getContentSize().width / 2);
			if (m_iCurTollgate == m_maxTollgateNum)
			{
				lv_left->setVisible(false);
			}
			else
			{
				lv_left->setVisible(true);
				lv_left->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(GetCurLevelName(m_iCurTollgate + 1)));
			}
		});
		auto rightMove = MoveTo::create(div_tm, (lv_right->getPosition()));
		auto call2 = CallFunc::create([&]() {
			slt_bar_yes->setPositionX(slt_bar_yes->getPositionX() + interval_pos);
			lv_right->setOpacity(lv_center->getOpacity());
			lv_center->setOpacity(lv_left->getOpacity());

			m_actionFlag = 0;

			auto tmp = lv_left;
			lv_left = lv_center;
			lv_center = lv_right;
			lv_right = tmp;
		});
		auto seq = Sequence::create(leftMove, call, rightMove, call2, nullptr);
		
		/* 中关卡图移动动作 */
		auto ctMove = MoveTo::create(tm, lv_left->getPosition());
		auto scale1 = ScaleTo::create(tm / 5, 1.2f);
		auto scale2 = ScaleTo::create(tm / 5 * 4, lv_left->getScaleX(),lv_left->getScaleY());
		auto ctSpawn = Spawn::create(ctMove, Sequence::create(scale1, scale2, nullptr), nullptr);
		log("pos:%f;l==%f,%f", lv_left->getPositionX(), lv_left->getScaleX(), lv_left->getScaleY());

		/* 右关卡图移动动作 */
		auto rtMove = MoveTo::create(tm, lv_center->getPosition());
		auto scale3 = ScaleTo::create(tm / 5 * 4, 1.2f);
		auto scale4 = ScaleTo::create(tm / 5, 1.0f);
		auto rtSpawn = Spawn::create(rtMove, Sequence::create(scale3, scale4, nullptr), nullptr);

		lv_left->runAction(seq);
		lv_right->runAction(rtSpawn);
		lv_center->runAction(ctSpawn);

		lv_right->setZOrder(lv_center->getZOrder());
		lv_center->setZOrder(lv_left->getZOrder());

	}
	else
	{
		m_iCurTollgate--;

		/* 右关卡图移动动作 */
		auto leftMove = MoveBy::create(div_tm, Vec2(lv_left->getPositionX() + lv_right->getContentSize().width / 2, 0));
		auto call = CallFunc::create([&]() {
			lv_right->setPositionX(-lv_right->getContentSize().width / 2);

			/* 滑动一次到头 */
			if (m_iCurTollgate == 1)
			{
				lv_right->setVisible(false);
			}
			else
			{
				lv_right->setVisible(true);
				lv_right->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(GetCurLevelName(m_iCurTollgate - 1)));
			}
			
		});
		auto rightMove = MoveTo::create(div_tm, (lv_left->getPosition()));
		auto call2 = CallFunc::create([&]() {
			slt_bar_yes->setPositionX(slt_bar_yes->getPositionX() - interval_pos);
			lv_left->setOpacity(lv_center->getOpacity());
			lv_center->setOpacity(lv_right->getOpacity());
			
			m_actionFlag = 0;

			auto tmp = lv_left;
			lv_left = lv_right;
			lv_right = lv_center;
			lv_center = tmp;
		});
		auto seq = Sequence::create(leftMove, call, rightMove, call2, nullptr);

		/* 中关卡图移动动作 */
		auto ctMove = MoveTo::create(tm, lv_right->getPosition());
		auto scale1 = ScaleTo::create(tm / 5, 1.2f);
		auto scale2 = ScaleTo::create(tm / 5 * 4, lv_right->getScaleX(), lv_right->getScaleY());
		auto ctSpawn = Spawn::create(ctMove, Sequence::create(scale1, scale2, nullptr), nullptr);

		log("pos:%f;r==%f,%f", lv_right->getPositionX(),lv_right->getScaleX(), lv_right->getScaleY());

		/* 左关卡图移动动作 */
		auto rtMove = MoveTo::create(tm, lv_center->getPosition());
		auto scale3 = ScaleTo::create(tm / 5 * 4, 1.2f);
		auto scale4 = ScaleTo::create(tm / 5
			, 1.0f);
		auto rtSpawn = Spawn::create(rtMove, Sequence::create(scale3, scale4, nullptr), nullptr);
		
		lv_left->runAction(rtSpawn);
		lv_right->runAction(seq);
		lv_center->runAction(ctSpawn);

		lv_left->setZOrder(lv_center->getZOrder());
		lv_center->setZOrder(lv_right->getZOrder());
		
	}
	
}

void SelectTollgateScene::bindTouchListener()
{
	/* 设置遮罩层 */
	auto clipLayer = dynamic_cast<Sprite*>(bgLayer->getChildByName("clipLayer"));
	clipLayer->setZOrder(1);

	auto eventListener = EventListenerTouchOneByOne::create();

	eventListener->onTouchBegan = [&](Touch* _touch, Event* _event) {
		m_sPos = DIRECTOR->convertToGL(_touch->getLocationInView());
		m_isCountTime = true;
		return true;
	};

	eventListener->onTouchMoved = [&](Touch* _touch, Event* _event) {
		m_isSliding = true;
		return ;
	};

	eventListener->onTouchEnded = [&](Touch* _touch, Event* _event) {
		if (m_isSliding && m_actionFlag == 0)
		{
			m_ePos = DIRECTOR->convertToGL(_touch->getLocationInView());
			if (abs(m_ePos.x - m_sPos.x) > 10)
			{
				auto tm = m_touchTime > 0.5f ? 0.5f : m_touchTime;
				tm = tm < 0.1f ? 0.1f : tm;

				// 左滑
				if (m_ePos.x < m_sPos.x - 10)
				{
					/* 滑动关卡 */
					updateUI(true, tm);
					m_actionFlag = -1;
					
				}
				else if (m_ePos.x > m_sPos.x + 10)
				{// 右滑

				 /* 滑动关卡 */
					updateUI(false, tm);
					m_actionFlag = 1;
				}

				PLAY_EFFECT(PATH_SLID_SOUND, false);

				m_touchTime = 0;
				m_isCountTime = false;
			}
			m_isSliding = false;
		}
		else if (!m_isSliding)
		{
			auto pos = DIRECTOR->convertToGL(_touch->getLocationInView());
			if (boundBox.containsPoint(pos))
			{
				PLAY_EFFECT(PATH_ENTER_SOUND, false);
				enterCurTollgateScene();
			}
			
		}
		
	};

	eventListener->onTouchCancelled = eventListener->onTouchEnded;
	eventListener->setSwallowTouches(true);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, clipLayer);

}

void SelectTollgateScene::enterCurTollgateScene()
{
	setIntToXML(CURRENT_TOLLGATE, m_iCurTollgate);
	USERDEFAULT->flush();

	auto scale1 = ScaleTo::create(0.1f, 1.1f);
	auto scale2 = ScaleTo::create(0.1f, 1.0f);

	lv_center->runAction(Sequence::create(scale1,scale2, nullptr));
	this->runAction(DelayTime::create(0.25f));

	SceneManager::getInstance()->changeCurSceneType(SceneType::en_Tollgate_Scene);
}




