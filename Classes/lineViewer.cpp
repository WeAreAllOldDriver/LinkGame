#include "lineViewer.h"

static lineViewer* _sharedLineViewer = nullptr;

lineViewer* lineViewer::getInstance()
{
	//lineViewer* pRet = nullptr;
	if (!_sharedLineViewer)
	{
		_sharedLineViewer = new lineViewer();
		_sharedLineViewer->init();
	}

	return _sharedLineViewer;
}

bool lineViewer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init()); 

		_drawNode = DrawNode::create();
		this->addChild(_drawNode);
		_state = state::WAIT_TO_DRAW;
		bRet = true;
	} while (0);
	return bRet;
}

void lineViewer::addLine(Point a, Point b)
{
	Line l(a, b);
	_lines.push_back(l);
	
}

void lineViewer::showDirection()
{
	for (auto line : _lines)
	{
		_drawNode->drawSegment(line.left, line.right, 1, Color4F::BLACK);
		CCLOG("draw line from (%f, %f) to (%f, %f)", line.left.x, line.left.y,
			line.right.x, line.right.y);
	}
	auto action = Sequence::create(DelayTime::create(0.7f),
		CCCallFunc::create(this, callfunc_selector(lineViewer::clearLines)), NULL);
	this->runAction(action);
	//_state = state::WAIT_TO_CLEAR;
}

void lineViewer::clearLines()
{
	//if (_state == state::WAIT_TO_CLEAR){
		_drawNode->clear();
		_lines.clear();
		//_state = state::WAIT_TO_DRAW;
	//}
}