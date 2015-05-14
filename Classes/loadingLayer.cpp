#include "loadingLayer.h"
#include "gameLayer.h"

using namespace CocosDenshion;

bool loadingLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		auto WndSize = Director::getInstance()->getWinSize();

		auto brand = Sprite::create("brand.png");
		brand->setPosition(Point(WndSize.width / 2, WndSize.height / 2));
		this->addChild(brand);

		//auto cache = TextureCache::getInstance();
		auto action = Sequence::createWithTwoActions(DelayTime::create(0.1f),
			CCCallFunc::create(this, callfunc_selector(loadingLayer::loadingCallback)));
		this->runAction(action);
	//	cache->addImageAsync("atlas.png", CC_CALLBACK_1(loadingLayer::loadingCallback, this));
		
		bRet = true;
	} while (0);
	return bRet;
}

void loadingLayer::loadingCallback()
{
	/*
	AtlasLoader::getInstance()->loadAtlas("atlas.txt", texture);

	// After loading the texture , preload all the sound
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_die.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_hit.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_swooshing.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_wing.ogg");
	*/
	//then shift the scene
	auto scene = gameLayer::createScene();
	auto transitionScene = TransitionFade::create(2.0, scene);
	Director::getInstance()->replaceScene(transitionScene);

   }

Scene* loadingLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = loadingLayer::create();
	scene->addChild(layer);
	return scene;

}