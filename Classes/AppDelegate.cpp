#include "AppDelegate.h"

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        //glview = GLView::create("Brave C++ version");
		glview = GLViewImpl::createWithRect("brave", Rect(0, 0, 960, 640));
		glview->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // create a scene. it's an autorelease object
    //auto scene = StartScene::createScene();
	auto scene = GameScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
	if (this->getMusic()){
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
	// if you use SimpleAudioEngine, it must resume here
	if (this->getMusic()){
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}

bool AppDelegate::getMusic(){
	return this->_music;
}
bool AppDelegate::setMusic(bool music){
	this->_music = music;
	return this->_music;
}
bool AppDelegate::getSound(){
	return this->_sound;
}
bool AppDelegate::setSound(bool sound){
	this->_sound = sound;
	return this->_sound;
}