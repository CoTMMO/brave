#ifndef __CustomTool__
#define __CustomTool__
#include "cocos2d.h"

USING_NS_CC;

class CustomTool : public Ref
{
public:
	static CustomTool* getInstance();
	/*
	create MenueItemImage with SpriteFrameName
	*/
	static MenuItemImage* createMenuItemImage(const char* normal, const char* selected, ccMenuCallback callback);
	static MenuItemImage* createMenuItemImageFromImg(const char* normal, const char* selected, ccMenuCallback callback);
	static Animation* createAnimation(const char* animation_name, const char* pattern, int start, int end, float delay);
	static Animation* getAnimation(const char* animation_name);
private:
	static CustomTool* _tool;
};

#endif