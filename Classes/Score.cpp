#include "Score.h"

static ScoreDisplay* _sharedScoreDiaplay = nullptr;

ScoreDisplay* ScoreDisplay::getInstance()
{
	if (!_sharedScoreDiaplay)
	{
		_sharedScoreDiaplay = new ScoreDisplay();
		_sharedScoreDiaplay->init();
	}
	return _sharedScoreDiaplay;
}

bool ScoreDisplay::init()
{
	bool bRet = false;
	do
	{

		CC_BREAK_IF(!Node::init());

		//进度条
		_timer = ProgressTimer::create(Sprite::create("progressbarin.png"));
		_timer->setType(ProgressTimerType::BAR);
		_timer->setMidpoint(Point(0, 0));
		_timer->setBarChangeRate(Point(1, 0));
		_timer->setPercentage(0);
		_timer->setPosition(Point::ZERO);
		this->addChild(_timer);

		/*
		//进度条上的文字
		_label = Label::create("0\%", "Marker Felt", 20);
		_label->setPosition(Point(30, 35));
		_label->setColor(Color3B::BLACK);
		this->addChild(_label);*/

		auto bg = Sprite::create("progressbarBG.png");
		bg->setPosition(Point::ZERO);
		this->addChild(bg);

		_numberLinkItems = 0;

	} while (0);
	return bRet;
}

void ScoreDisplay::setProgress(int p)
{
	auto action = ProgressFromTo::create(0.5, _numberLinkItems, p);
	_numberLinkItems = p;
	_timer->runAction(action);

//	char buf[100];
//	sprintf(buf, "%d", _numberLinkItems);
	//_label->setString(buf);
}

void ScoreDisplay::addProgress()
{
	auto action = ProgressFromTo::create(0.5, _numberLinkItems, _numberLinkItems + 2);
	_numberLinkItems += 2;
	_timer->runAction(action);
	//char buf[100];
	//sprintf(buf, "%d", _numberLinkItems);
//	_label->setString(buf);
}

void ScoreDisplay::reset()
{/*
	_numberLinkItems = 0;
	_timer->setPercentage(0);*/
	setProgress(0);
}