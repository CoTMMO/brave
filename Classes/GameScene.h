#ifndef __GameScene__
#define __GameScene__
#include "cocos2d.h"
#include "GameBg.h"

USING_NS_CC;

class GameScene : public Layer
{
private:
	void update(float time);
	virtual void onExit();
	GameBg* _background;
	Sprite* _role;
	bool _flip;
	float _speed;
	EventListenerTouchOneByOne* _listener_touch;
	Sprite* _circle;
public:
	bool init();
	static Scene* createScene();
	CREATE_FUNC(GameScene);
	bool onTouchBegan(Touch* touch, Event* event);
	void onClose(Ref* obj);
	void onLeft(Ref* obj);
	void onRight(Ref* obj);
	void onGo(Vec2 dest);
	void onAttack(Ref* obj);
	void onAttack1(Ref* obj);
	void onAttack2(Ref* obj);
	void onAttack3(Ref* obj);
	void onAttack4(Ref* obj);
	void onIdle();
};

#endif