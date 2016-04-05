#include "GameScene.h"
#include "GameBg.h"
#include <math.h>
#include "CustomTool.h"

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
		_background->setPosition(Vec2(0, 0));
		this->addChild(_background, -1);

		Sprite* map = Sprite::create("scene/bg_1.png");
		map->setScale(visibleSize.height * 4 / 5 / map->getContentSize().height);
		map->setAnchorPoint(Vec2(0, 1));
		map->setPosition(Vec2(0, visibleSize.height));
		this->addChild(map, -2);

		//关闭按钮
		MenuItemImage *pCloseItem = CustomTool::createMenuItemImageFromImg("button/button_close.png", "button/button_close.png", CC_CALLBACK_1(GameScene::onClose, this));
		CC_BREAK_IF(!pCloseItem);
		pCloseItem->setPosition(Vec2(visibleSize.width - pCloseItem->getContentSize().width / 2, visibleSize.height - pCloseItem->getContentSize().height / 2));
		Menu* pMenu1 = Menu::create(pCloseItem, NULL);
		pMenu1->setPosition(Point::ZERO);
		CC_BREAK_IF(!pMenu1);
		this->addChild(pMenu1, 1);
		//移动按钮
		MenuItemImage *pLeftButtonItem = CustomTool::createMenuItemImageFromImg("button/button_go.png", "button/button_go.png", CC_CALLBACK_1(GameScene::onLeft, this));
		CC_BREAK_IF(!pLeftButtonItem);
		pLeftButtonItem->setRotationSkewY(180);
		pLeftButtonItem->setPosition(Vec2(pLeftButtonItem->getContentSize().width / 2, pLeftButtonItem->getContentSize().height/2));
		
		MenuItemImage *pRightButtonItem = CustomTool::createMenuItemImageFromImg("button/button_go.png", "button/button_go.png", CC_CALLBACK_1(GameScene::onRight, this));
		CC_BREAK_IF(!pRightButtonItem);
		pRightButtonItem->setPosition(Vec2(pRightButtonItem->getContentSize().width * 3 / 2, pRightButtonItem->getContentSize().height / 2));
		
		Menu* pMenuGo = Menu::create(pLeftButtonItem, pRightButtonItem, NULL);
		pMenuGo->setPosition(Point::ZERO);
		CC_BREAK_IF(!pMenuGo);
		this->addChild(pMenuGo, 1);
		//攻击按钮
		MenuItemImage *pAttackItem = CustomTool::createMenuItemImageFromImg("button/button_attack.png", "button/button_attack.png", CC_CALLBACK_1(GameScene::onAttack, this));
		CC_BREAK_IF(!pAttackItem);
		pAttackItem->setPosition(Vec2(visibleSize.width - pAttackItem->getContentSize().width / 2, pAttackItem->getContentSize().height / 2));

		MenuItemImage *pAttack1Item = CustomTool::createMenuItemImageFromImg("button/1001_1.png", "button/1001_1.png", CC_CALLBACK_1(GameScene::onAttack1, this)); 
		CC_BREAK_IF(!pAttack1Item);
		pAttack1Item->setPosition(Vec2(visibleSize.width - pAttackItem->getContentSize().width - pAttack1Item->getContentSize().width/2, pAttack1Item->getContentSize().height/2));

		MenuItemImage *pAttack2Item = CustomTool::createMenuItemImageFromImg("button/1001_2.png", "button/1001_2.png", CC_CALLBACK_1(GameScene::onAttack2, this)); 
		CC_BREAK_IF(!pAttack2Item);
		pAttack2Item->setPosition(Vec2(visibleSize.width - (pAttackItem->getContentSize().width + pAttack2Item->getContentSize().width / 2) * 2 / sqrt(5), (pAttackItem->getContentSize().width + pAttack2Item->getContentSize().width / 2) / sqrt(5) + pAttack2Item->getContentSize().height/3));


		MenuItemImage *pAttack3Item = CustomTool::createMenuItemImageFromImg("button/1001_3.png", "button/1001_3.png", CC_CALLBACK_1(GameScene::onAttack3, this)); 
		CC_BREAK_IF(!pAttack3Item);
		pAttack3Item->setPosition(Vec2(visibleSize.width - (pAttackItem->getContentSize().width + pAttack3Item->getContentSize().width / 3) / sqrt(5) - pAttack3Item->getContentSize().width/2, (pAttackItem->getContentSize().width + pAttack3Item->getContentSize().width / 2) * 2 / sqrt(5)));

		MenuItemImage *pAttack4Item = CustomTool::createMenuItemImageFromImg("button/1001_4.png", "button/1001_4.png", CC_CALLBACK_1(GameScene::onAttack4, this)); 
		CC_BREAK_IF(!pAttack4Item);
		pAttack4Item->setPosition(Vec2(visibleSize.width - pAttack4Item->getContentSize().width/2, pAttackItem->getContentSize().height + pAttack4Item->getContentSize().height/2));

		Menu* pMenuAttack = Menu::create(pAttackItem, pAttack1Item, pAttack2Item, pAttack3Item, pAttack4Item, NULL);
		pMenuAttack->setPosition(Point::ZERO);
		CC_BREAK_IF(!pMenuAttack);
		this->addChild(pMenuAttack, 1);

		//点击动画
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("effect/click_role.plist", "effect/click_role.png");
		auto animation = CustomTool::createAnimation("click_role", "click_role/%04d", 0, 11, 0.05f);
		
		_circle = Sprite::createWithSpriteFrameName("click_role/0000");
		_circle->setVisible(false);
		this->addChild(_circle,2);
		

		//预加载动画
		/*
		0-33 空闲
		34-65 走路

		66-87 左劈
		87-107 右劈
		108-135 撞击
		136-163 挑起
		164-188 大砍

		189-232 技能一挑砍
		233-265 技能二地震
		266-331 技能三旋转
		332-388 技能四插地
		*/

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("roleanimate/1001_effup.plist", "roleanimate/1001_effup.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("roleanimate/1001_role.plist", "roleanimate/1001_role.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/role.plist", "image/role.pvr.ccz");

		auto animation_idle = CustomTool::createAnimation("1001_role_idle", "1001_role/%04d", 0, 33, 0.05f);

		auto animation_walk = CustomTool::createAnimation("1001_role_walk", "1001_role/%04d", 34, 65, 0.05f);

		auto animation_attack = CustomTool::createAnimation("1001_role_attack", "1001_role/%04d", 66, 188, 0.05f);
		auto animation_attack_effup = CustomTool::createAnimation("1001_effup_attack", "1001_effup/%04d", 66, 188, 0.05f);

		CustomTool::createAnimation("1001_role_attack1", "1001_role/%04d", 189, 232, 0.05f);
		CustomTool::createAnimation("1001_effup_attack1", "1001_effup/%04d", 189, 232, 0.05f);

		CustomTool::createAnimation("1001_role_attack2", "1001_role/%04d", 233, 265, 0.05f);
		CustomTool::createAnimation("1001_effup_attack2", "1001_effup/%04d", 233, 265, 0.05f);

		CustomTool::createAnimation("1001_role_attack3", "1001_role/%04d", 266, 331, 0.05f);
		CustomTool::createAnimation("1001_effup_attack3", "1001_effup/%04d", 266, 331, 0.05f);

		CustomTool::createAnimation("1001_role_attack4", "1001_role/%04d", 332, 388, 0.05f);
		CustomTool::createAnimation("1001_effup_attack4", "1001_effup/%04d", 332, 388, 0.05f);



		//角色加载
		_role = Sprite::createWithSpriteFrameName("1001_role/0040");
		//_role->setContentSize(Size(_role->getTextureRect().size.width, _role->getTextureRect().size.height));
		//_role->setAnchorPoint(Vec2(0.5, 0.5));
		_role->setPosition(Vec2(_role->getTextureRect().size.width, (visibleSize.height * 2 / 5)));
		log("_role size:%f,%f", _role->getContentSize().width, _role->getContentSize().height);
		log("_role position:%f,%f",_role->getPositionX(),_role->getPositionY());
		_flip = true;
		this->addChild(_role, 10);

		auto _effup = Sprite::createWithSpriteFrameName("1001_effup/0040");
		_effup->setName("effup");
		//_effup->setContentSize(Size(_role->getTextureRect().size.width, _role->getTextureRect().size.height));
		//_effup->setAnchorPoint(Vec2(0.5, 0.5));
		_effup->setPosition(Vec2(_role->getContentSize().width / 2, (visibleSize.height * 2 / 5)));
		log("_effup size:%f,%f", _effup->getContentSize().width, _effup->getContentSize().height);
		log("_effup position:%f,%f", _role->getPositionX(), _role->getPositionY());
		_role->addChild(_effup);

		LabelTTF *_label = LabelTTF::create("skynet", "Consolas", 30);
		//_label->setContentSize(Size(_role->getTextureRect().size.width, _role->getTextureRect().size.height));
		//_label->setAnchorPoint(Vec2(0.5, 0.5));
		_label->setPosition(_role->getContentSize().width / 2, (visibleSize.height * 2 / 5) + _role->getTextureRect().size.height);
		log("_label size:%f,%f", _label->getContentSize().width, _label->getContentSize().height);
		log("_label position:%f,%f", _label->getPositionX(), _label->getPositionY());
		_label->setName("label");
		_role->addChild(_label);

		this->onIdle();//角色idle动画

		//点击操作
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
	//_role->getChildByName("effup")->setPosition(_role->getPosition());
	//_role->getChildByName("label")->setPosition(_role->getPosition());
}

void GameScene::onExit()
{
	this->unscheduleUpdate();
	Layer::onExit();
}

void GameScene::onIdle()
{
	_role->stopAllActions();
	_role->getChildByName("effup")->stopAllActions();
	//获取动画
	auto animation = CustomTool::getAnimation("1001_role_idle");
	auto animate = RepeatForever::create(Animate::create(animation));

	_role->runAction(animate);
	log("onIdle");
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 dest = this->convertToNodeSpace(touch->getLocation());
	log("log click:%f,%f", dest.x,dest.y);
	//this->onGo(dest);

	_circle->stopAllActions();
	auto animation = CustomTool::getAnimation("click_role");
	auto animate = Animate::create(animation);
	auto func = [&]()
	{
		_circle->stopAllActions();
		_circle->setVisible(false);
	};
	auto callback = CallFunc::create(func);
	auto seq = Sequence::create(animate, callback, nullptr);
	_circle->setPosition(dest);
	_circle->setVisible(true);
	_circle->runAction(seq);

	return true;
}

void GameScene::onGo(Vec2 dest)
{
	_role->stopAllActions();
	_background->stopActionByTag(1);

	auto curPos = _role->getPosition();

	//改变面向
	if (curPos.x > dest.x && _flip)
	{
		//log("chang to left");
		_flip = false;
		_role->setFlippedX(true);
		//_role->getChildByName("effup")->setFlippedX(true);
	}
	else if (curPos.x < dest.x && !_flip)
	{
		//log("chang to right");
		_flip = true;
		_role->setFlippedX(false);
		//_role->getChildByName("effup")->setFlippedX(false);
	}
	//log("_flip:%d", _flip);

	//时间
	auto diff = dest - curPos;
	auto time = diff.getLength() / _speed;

	//运动距离
	Vec2 _role_dest = _role->getPosition();
	Vec2 _bg_dest = _background->getPosition();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto _rb = _role->getPositionX() - _background->getPositionX();//实体与背景距离
	auto _db = dest.x - _background->getPositionX();//目的与背景距离
	if (_rb <= visibleSize.width / 2){
		if (_db < (visibleSize.width / 2)){
			_role_dest = dest;
			log("position:l l");
		}
		else{
			_role_dest = Vec2(visibleSize.width / 2, dest.y);
			_bg_dest = Vec2(_background->getPositionX() - (_db - visibleSize.width / 2), 0);
			log("position:l m");
		}

	}
	else if (_rb >= (_background->getContentSize().width - visibleSize.width / 2)){
		if (_db > (_background->getContentSize().width - visibleSize.width / 2)){
			_role_dest = dest;
			log("position:r r");
		}
		else{
			_role_dest = Vec2(visibleSize.width / 2, dest.y);
			_bg_dest = Vec2(_background->getPositionX() + ((_background->getContentSize().width - visibleSize.width / 2) - _db), 0);
			log("position:r m");
		}
	}
	else{
		if (_db<visibleSize.width / 2){
			_role_dest = Vec2(_db, dest.y);
			_bg_dest = Vec2(_background->getPositionX() + (_rb - visibleSize.width / 2), 0);
			log("position:m l");
		}
		else if (_db>(_background->getContentSize().width - visibleSize.width / 2)){
			_role_dest = Vec2(_db - (_background->getContentSize().width - visibleSize.width), dest.y);
			_bg_dest = Vec2(_background->getPositionX() - ((_background->getContentSize().width - visibleSize.width / 2) - _rb), 0);
			log("position:m r");
		}
		else{
			_role_dest = Vec2(visibleSize.width / 2, dest.y);
			_bg_dest = Vec2(_background->getPositionX() - (dest.x - _role->getPositionX()), 0);
			log("position:m m");
		}
	}

	//获取动画
	auto animation = CustomTool::getAnimation("1001_role_walk");
	auto animate = RepeatForever::create(Animate::create(animation));
	animate->setTag(2);
	_role->runAction(animate);

	if (_role_dest != _role->getPosition()){
		auto move = MoveTo::create(time, _role_dest);
		auto func = [&]()
		{
			this->onIdle();
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
			this->onIdle();
			log("move bg ok");
		};
		auto callback2 = CallFunc::create(func2);
		auto seq2 = Sequence::create(move2, callback2, nullptr);
		seq2->setTag(1);
		_background->runAction(seq2);
	}
}

void GameScene::onClose(Ref* obj)
{
	Director::getInstance()->end();
}
void GameScene::onLeft(Ref* obj)
{
	float _rb = _role->getPositionX() - _background->getPositionX()-200;
	if (_rb > 0){
		this->onGo(Vec2(_role->getPositionX() - 200, _role->getPositionY()));
	}
}
void GameScene::onRight(Ref* obj)
{
	float _rb = _role->getPositionX() - _background->getPositionX() + 200;
	if (_rb < _background->getContentSize().width){
		this->onGo(Vec2(_role->getPositionX() + 200, _role->getPositionY()));
	}
}

void GameScene::onAttack(Ref* obj)
{
	_role->stopAllActions();
	_role->getChildByName("effup")->stopAllActions();
	//获取动画
	auto animation = CustomTool::getAnimation("1001_role_attack");
	auto animate_role = Animate::create(animation);
	auto func = [&]()
	{
		this->onIdle();
	};
	auto callback = CallFunc::create(func);
	auto animate = Sequence::create(animate_role, callback, nullptr);

	auto animation_effup = CustomTool::getAnimation("1001_effup_attack");
	auto animate_effup = Animate::create(animation_effup);

	_role->runAction(animate);
	_role->getChildByName("effup")->runAction(animate_effup);
	log("onAttack");
}
void GameScene::onAttack1(Ref* obj)
{
	_role->stopAllActions();
	_role->getChildByName("effup")->stopAllActions();
	//获取动画
	auto animation = CustomTool::getAnimation("1001_role_attack1");
	auto animate_role = Animate::create(animation);
	auto func = [&]()
	{
		this->onIdle();
	};
	auto callback = CallFunc::create(func);
	auto animate = Sequence::create(animate_role, callback, nullptr);

	auto animation_effup = CustomTool::getAnimation("1001_effup_attack1");
	auto animate_effup = Animate::create(animation_effup);

	_role->runAction(animate);
	_role->getChildByName("effup")->runAction(animate_effup);
	log("onAttack1");
}
void GameScene::onAttack2(Ref* obj)
{
	_role->stopAllActions();
	_role->getChildByName("effup")->stopAllActions();
	//获取动画
	auto animation = CustomTool::getAnimation("1001_role_attack2");
	auto animate_role = Animate::create(animation);
	auto func = [&]()
	{
		this->onIdle();
	};
	auto callback = CallFunc::create(func);
	auto animate = Sequence::create(animate_role, callback, nullptr);

	auto animation_effup = CustomTool::getAnimation("1001_effup_attack2");
	auto animate_effup = Animate::create(animation_effup);

	_role->runAction(animate);
	_role->getChildByName("effup")->runAction(animate_effup);
	log("onAttack2");
}
void GameScene::onAttack3(Ref* obj)
{
	_role->stopAllActions();
	_role->getChildByName("effup")->stopAllActions();
	//获取动画
	auto animation = CustomTool::getAnimation("1001_role_attack3");
	auto animate_role = Animate::create(animation);
	auto func = [&]()
	{
		this->onIdle();
	};
	auto callback = CallFunc::create(func);
	auto animate = Sequence::create(animate_role, callback, nullptr);

	auto animation_effup = CustomTool::getAnimation("1001_effup_attack3");
	auto animate_effup = Animate::create(animation_effup);

	_role->runAction(animate);
	_role->getChildByName("effup")->runAction(animate_effup);
	log("onAttack3");
}
void GameScene::onAttack4(Ref* obj)
{
	_role->stopAllActions();
	_role->getChildByName("effup")->stopAllActions();
	//获取动画
	auto animation = CustomTool::getAnimation("1001_role_attack4");
	auto animate_role = Animate::create(animation);
	auto func = [&]()
	{
		this->onIdle();
	};
	auto callback = CallFunc::create(func);
	auto animate = Sequence::create(animate_role, callback, nullptr);

	auto animation_effup = CustomTool::getAnimation("1001_effup_attack4");
	auto animate_effup = Animate::create(animation_effup);

	_role->runAction(animate);
	_role->getChildByName("effup")->runAction(animate_effup);
	log("onAttack4");
}