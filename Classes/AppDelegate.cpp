#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "loadingLayer.h"
USING_NS_CC;

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
        glview = GLView::create("Lianliankan");
        director->setOpenGLView(glview);
    }

	//set resolution size
	glview->setDesignResolutionSize(960, 640, ResolutionPolicy::EXACT_FIT);

    // turn on display FPS
    director->setDisplayStats(true);

	//set resource search path
	this->setResourcePath();

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = loadingLayer::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::setResourcePath()
{
	std::vector<std::string> path;
	path.push_back("image");
	path.push_back("sounds");
	path.push_back("font");
	FileUtils::getInstance()->setSearchPaths(path);
}