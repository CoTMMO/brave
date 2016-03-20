#include "GameScene.h"
#include "GameBg.h"

bool GameScene::init()
{
	bool bRet = false;
	do
	{
		if (!Layer::init())
			return false;
		log("Game::init");

		_speed = 100;

		Size visibleSize = CCDirector::getInstance()->getVisibleSize();
		Point origin = CCDirector::getInstance()->getVisibleOrigin();

		//背景
		_background = GameBg::create();
		_background->setPosition(Vec2(30,30));
		this->addChild(_background, 0);
		
		//按钮
		MenuItemImage *pCloseItem = MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(GameScene::onMove, this)
			);
		CC_BREAK_IF(!pCloseItem);
		pCloseItem->setPosition(Vec2(visibleSize.width - 20, visibleSize.height - 20));
		Menu* pMenu1 = Menu::create(pCloseItem, NULL);
		pMenu1->setPosition(Point::ZERO);
		CC_BREAK_IF(!pMenu1);
		this->addChild(pMenu1, 1);

		//预加载动画
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("roleanimate/1001_effup.plist", "roleanimate/1001_effup.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("roleanimate/1001_role.plist", "roleanimate/1001_role.png");
		auto animation1 = Animation::create();
		animation1->setDelayPerUnit(0.1f);
		auto animation2 = Animation::create();
		animation2->setDelayPerUnit(0.1f);
		for (int j = 0; j < 439; j++){
			auto sfName = String::createWithFormat("1001_effup/%04d", j)->getCString();
			auto sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName);
			animation1->addSpriteFrame(sf);

			auto sfName2 = String::createWithFormat("1001_role/%04d", j)->getCString();
			auto sf2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName2);
			animation2->addSpriteFrame(sf2);
		}
		AnimationCache::getInstance()->addAnimation(animation1, String::create("1001_effup")->getCString());
		AnimationCache::getInstance()->addAnimation(animation2, String::create("1001_role")->getCString());

		//获取动画
		//auto animation2 = AnimationCache::getInstance()->getAnimation(String::create("1001_role")->getCString());
		auto animate2 = RepeatForever::create(Animate::create(animation2));
		animate2->setTag(2);

		//加载角色并运行动画
		_position = Vec2(visibleSize.width / 2, visibleSize.height / 2);
		_role = Sprite::create("CloseNormal.png");
		_role->setPosition(_position);
		_flip = true;
		_role->runAction(animate2);
		this->addChild(_role, 2);

		_listener_touch = EventListenerTouchOneByOne::create();
		_listener_touch->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener_touch, this);

		//定时调用
		this->scheduleUpdate();

		bRet = true;
	} while (0);

	return bRet;
}


Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene::create();
	scene->addChild(layer, 1);

	return scene;
}

void GameScene::update(float time)
{
	//if (_position != _role->getPosition()){
	//	if (_position.x - _role->getPosition().x)
	//}
	log("GameScene::update");
}

void GameScene::onExit()
{
	this->unscheduleUpdate();
	Layer::onExit();
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 dest = this->convertToNodeSpace(touch->getLocation());
	auto _rX = _role->getPositionX();
	auto _bS = _background->getContentSize().width;
	auto _bX = _background->getPositionX();
	auto _vS = Director::getInstance()->getVisibleSize().width;
	
	auto curPos = _role->getPosition();
	if (curPos.x < dest.x && _flip)
	{

		_flip = false;
		_role->setFlippedX(true);
	}
	else
	{
		_flip = true;
		_role->setFlippedX(true);
	}
	//_role->setPosition(dest);
	_position = dest;
	//	log("MainScene::onTouchBegan");

	auto diff = dest - curPos;
	auto time = diff.getLength() / _speed;
	auto move = MoveTo::create(time, dest);
	auto func = [&]()
	{
		log("move ok");
	};
	auto callback = CallFunc::create(func);
	auto seq = Sequence::create(move, callback, nullptr);
	seq->setTag(5);
	_role->runAction(seq);


	return true;
}

void GameScene::onMove(Ref* obj)
{
	Size visibleSize = CCDirector::getInstance()->getVisibleSize();
	Point origin = CCDirector::getInstance()->getVisibleOrigin();
	_background->setPositionX(_background->getPositionX() - 50);
	log("GameScene::onRight");
}