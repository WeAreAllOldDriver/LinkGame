/*
 * 连连看游戏按钮
 * 按下 图标四周亮起
 * 进入可选阶段，若下一个可以连接则消除
 * 不行则恢复未选中状态
 * 在选中状态下再按一次取消选中
 */

#pragma once
#include "cocos2d.h"

USING_NS_CC;
class iPoint
{
public:
	int x, y;
	iPoint():x(0),y(0) {}; 
	iPoint(int a, int b) :x(a), y(b)
	{}

};
class nodeItem: public Node
{
public:
	enum class nodeState
	{
		NORMAL,
		SELECTED
	};

private:
	Sprite* _normalImage;
	Sprite* _selectedImage;
	nodeState _currentState;
public:
	static nodeItem* create(const std::string& normal,const std::string& selected);
	//vector
	//static nodeItem* create(Vector<std::string&> strs);
	static nodeItem* randomCreate();
	static nodeItem* createByType(int type);
	virtual bool init(const std::string& normal, const std::string& selected);
	nodeState getCurrentState() { return _currentState; }
	void changeType(int type);
	
	CC_SYNTHESIZE(int, _nodeType, Type);
	CC_SYNTHESIZE(iPoint, _posInMatrix, PosInMatrix);
	//int nodeType;

	void selectNode();
	void cancelNode();
	void removeNode();

	Size getImageSize() const { return _normalImage->getContentSize(); }
	Rect rect()  const;
	float getItemZPosition() { return _normalImage->getPositionZ(); }
};