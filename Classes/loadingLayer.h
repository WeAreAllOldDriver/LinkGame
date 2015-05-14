#pragma once

#include "cocos2d.h"

USING_NS_CC;

class loadingLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(loadingLayer);
	static Scene* createScene();

	//call this function and replawhen 
	//void loadingCallback(Texture2D* texture);
	void loadingCallback();
};