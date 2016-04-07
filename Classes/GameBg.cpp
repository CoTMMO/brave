#include "GameBg.h"

bool GameBg::init()
{
	bool bRet = false;
	do
	{
		if (!Sprite::init())
			return false;

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();

		Sprite* map1 = Sprite::create("scene/bg_2.png");
		map1->setScale(visibleSize.height * 2 / 5 / map1->getContentSize().height);
		Sprite* map2 = Sprite::create("scene/bg_2.png");
		map2->setScale(visibleSize.height * 2 / 5 / map2->getContentSize().height);
		Sprite* map3 = Sprite::create("scene/bg_2.png");
		map3->setScale(visibleSize.height * 2 / 5 / map3->getContentSize().height);
		this->setContentSize(Size(map1->getContentSize().width + map2->getContentSize().width + map3->getContentSize().width, map1->getContentSize().height));
		map1->setAnchorPoint(Point(0, 0));
		map2->setAnchorPoint(Point(0, 0));
		map3->setAnchorPoint(Point(0, 0));
		map1->setPosition(Point(0, 0));
		map2->setPosition(Point(map1->getContentSize().width, 0));
		map3->setPosition(Point(map1->getContentSize().width + map2->getContentSize().width, 0));
		this->addChild(map1, 0, "map1");
		this->addChild(map2, 0, "map2");
		this->addChild(map3, 0, "map3");
		

		bRet = true;
	} while (0);

	return bRet;
}