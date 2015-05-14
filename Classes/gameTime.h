#pragma once
#include "cocos2d.h"

USING_NS_CC;

class gameTimer :public Node
{
public:
	virtual bool init();
	//CREATE_FUNC(gameTimer);
	static gameTimer* getInstance();
	void timeUpdate(float dt);
	float timePass;
	Label* _label;
	void reset(); 
	void start() { schedule(schedule_selector(gameTimer::timeUpdate), 0.1f); }
	void stop(){ unschedule(schedule_selector(gameTimer::timeUpdate)); }
};