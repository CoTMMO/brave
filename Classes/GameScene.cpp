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

		_speed = 400;

		Size visibleSize = CCDirector::getInstance()->getVisibleSize();
		Point origin = CCDirector::getInstance()->getVisibleOrigin();

		//背景
		_background = GameBg::create();
		_background->setAnchorPoint(Vec2(0, 0));
		_background->setPosition(Vec2(0,0));
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
		_role = Sprite::create("CloseNormal.png");
		//_role = Sprite::createWithSpriteFrameName("1001_role/0010");
		_role->setPosition(Vec2(0, 0));
		_flip = true;
		//_role->runAction(animate2);
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
	//log("GameScene::update");
}

void GameScene::onExit()
{
	this->unscheduleUpdate();
	Layer::onExit();
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	_role->stopActionByTag(1);
	_background->stopActionByTag(1);

	Vec2 dest = this->convertToNodeSpace(touch->getLocation());
	auto curPos = _role->getPosition();

	//改变面向
	if (curPos.x > dest.x && _flip)
	{
		//log("chang to left");
		_flip = false;
		_role->setFlippedX(true);
	}else if (curPos.x < dest.x && !_flip)
	{
		//log("chang to right");
		_flip = true;
		_role->setFlippedX(false);
	}
	//log("_flip:%d", _flip);

	//时间
	auto diff = dest - curPos;
	auto time = diff.getLength() / _speed;

	//运动距离
	Vec2 _role_dest=_role->getPosition();
	Vec2 _bg_dest=_background->getPosition();
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto _rb = _role->getPositionX() - _background->getPositionX();
	if (_rb<=visibleSize.width / 2){
		if ((dest.x - _background->getPositionX()) < (visibleSize.width / 2)){
			_role_dest = dest;
			log("position:1");
		}
		else{
			_role_dest = Vec2(visibleSize.width / 2, dest.y);
			_bg_dest = Vec2(-(dest.x-_background->getPositionX()-visibleSize.width/2), 0);
			log("position:2");
		}
		
	}
	else if (_rb>=(_background->getContentSize().width - visibleSize.width / 2)){
		if ((dest.x - _background->getPositionX()) > (_background->getContentSize().width - visibleSize.width / 2)){
			_role_dest = dest;
			log("position:3");
		}
		else{
			_role_dest = Vec2(visibleSize.width / 2, dest.y);
			_bg_dest = Vec2(_background->getPositionX() + (_background->getContentSize().width - visibleSize.width / 2) - (dest.x - _background->getPositionX()), 0);
			log("position:4");
		}
	}
	else{
		_role_dest = Vec2(visibleSize.width / 2, dest.y);
		_bg_dest = Vec2(_background->getPositionX() - (dest.x - _role->getPositionX()), 0);
		log("position:5");
	}

	if (_role_dest != _role->getPosition()){
		auto move = MoveTo::create(time, _role_dest);
		auto func = [&]()
		{
			log("move role ok");
		};
		auto callback = CallFunc::create(func);
		auto seq = Sequence::create(move, callback, nullptr);
		seq->setTag(1);
		_role->runAction(seq);
	}
	if (_bg_dest != _background->getPosition()){
		auto move2 = MoveTo::create(time, _bg_dest);
		auto func2 = [&]()
		{
			log("move bg ok");
		};
		auto callback2 = CallFunc::create(func2);
		auto seq2 = Sequence::create(move2, callback2, nullptr);
		seq2->setTag(1);
		_background->runAction(seq2);
	}
	

	
	return true;
}

void GameScene::onMove(Ref* obj)
{
	Size visibleSize = CCDirector::getInstance()->getVisibleSize();
	Point origin = CCDirector::getInstance()->getVisibleOrigin();
	_background->setPositionX(_background->getPositionX() - 50);
	log("GameScene::onRight");
}