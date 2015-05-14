#pragma once
#include "cocos2d.h"

USING_NS_CC;

/*
 * ��������item�м���������
 * 1s����ʧ
 */

class Line
{
public:
	Point left;
	Point right;
	Line() : left(Point(0, 0)), right(Point(0, 0)) {}
	Line(Point a, Point b){ left = a; right = b; }
};

class lineViewer: public Layer
{
public:
	static lineViewer* getInstance();
	virtual bool init();
	void addLine(Point a, Point b);
	void showDirection();
	void clearLines();

private:
	enum class state{
		WAIT_TO_DRAW,
		WAIT_TO_CLEAR
	};
	std::vector<Line> _lines;
	DrawNode* _drawNode;
	state _state;
};