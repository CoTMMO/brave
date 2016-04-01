#include "CustomTool.h"

CustomTool* CustomTool::_tool;

CustomTool* CustomTool::getInstance()
{
	if(!_tool)
	{
		_tool = new CustomTool();
	}

	return _tool;
}

MenuItemImage* CustomTool::createMenuItemImage(const char* normal, const char* selected, ccMenuCallback callback)
{
	auto item = MenuItemImage::create();
	auto nsf = SpriteFrameCache::getInstance()->getSpriteFrameByName(normal);
	auto ssf = SpriteFrameCache::getInstance()->getSpriteFrameByName(selected);
	item->setNormalSpriteFrame(nsf);
	item->setSelectedSpriteFrame(ssf);
	item->setCallback(callback);
	return item;
}

MenuItemImage* CustomTool::createMenuItemImageFromImg(const char* normal, const char* selected, ccMenuCallback callback)
{
	MenuItemImage *item = MenuItemImage::create(
		normal,
		selected,
		callback
		);
	return item;
}

Animation* CustomTool::createAnimation(const char* animation_name, const char* pattern, int start=0, int end=10, float delay = 0.05f)
{
	auto animation = Animation::create();
	animation->setDelayPerUnit(delay);
	for (int j = start; j <= end; j++){
		auto sfName = String::createWithFormat(pattern, j)->getCString();
		auto sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName);
		animation->addSpriteFrame(sf);
	}
	AnimationCache::getInstance()->addAnimation(animation, String::create(animation_name)->getCString());
	return animation;
}
Animation* CustomTool::getAnimation(const char* animation_name)
{
	auto animation = AnimationCache::getInstance()->getAnimation(String::create(animation_name)->getCString());
	return animation;
}