#include "gameTime.h"

static gameTimer* _sharedGameTimer = nullptr;
gameTimer* gameTimer::getInstance()
{
	if (!_sharedGameTimer)
	{
		_sharedGameTimer = new gameTimer();
		_sharedGameTimer->init();
	}
	return _sharedGameTimer;
}

bool gameTimer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());
		timePass = 0.0;
		char buf[100];
		sprintf(buf, "time: %.1f", timePass);
		//_label = Label::create(buf, "Marker Felt", 30);
		_label = Label::createWithTTF(buf, "fonts/Marker Felt.ttf", 30);
		_label->setAnchorPoint(Point(0, 1));
		_label->setPosition(Point::ZERO);
		_label->setColor(Color3B::BLACK);
		this->addChild(_label);

		schedule(schedule_selector(gameTimer::timeUpdate), 0.1f);
		bRet = true;
	} while (0);
	return bRet;
}

void gameTimer::timeUpdate(float dt)
{
	timePass += dt;
	char buf[100];
	sprintf(buf, "time: %.1f", timePass);
	_label->setString(buf);
}

void gameTimer::reset()
{
	timePass = 0;
	char buf[100];
	sprintf(buf, "time: %.1f", timePass);
	_label->setString(buf);
}