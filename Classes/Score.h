#pragma once
#include "cocos2d.h"

USING_NS_CC;

// Score

class ScoreDisplay:public Node
{
public:
	static ScoreDisplay* getInstance();
	virtual bool init();
	//set progress 
	void setProgress(int p);

	//add progress when two items link up
	void addProgress();
	const Size& getImageSize() const { return _timer->getContentSize(); }
	void reset();
private:
	ProgressTimer* _timer;
	int _numberLinkItems;
	//Label* _label;
};