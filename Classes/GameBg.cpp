#include "GameBg.h"

bool GameBg::init()
{
	bool bRet = false;
	do
	{
		if (!Layer::init())
			return false;
		log("GameBg::init");

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();

		Sprite* map1 = Sprite::create("image/bg1.png");
		Sprite* map2 = Sprite::create("image/bg2.png");
		Sprite* map3 = Sprite::create("image/bg3.png");
		map1->setPosition(Vec2(map1->getContentSize().width / 2 + origin.x, map1->getContentSize().height / 2 + origin.y));
		map2->setPosition(Vec2(map2->getContentSize().width / 2 + origin.x + map2->getContentSize().width, map2->getContentSize().height / 2 + origin.y));
		this->addChild(map1, 0, "map1");
		this->addChild(map2, 0, "map2");

		bRet = true;
	} while (0);

	return bRet;
}