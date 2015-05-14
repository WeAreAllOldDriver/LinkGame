/*
 * ��������Ϸ��ť
 * ���� ͼ����������
 * �����ѡ�׶Σ�����һ����������������
 * ������ָ�δѡ��״̬
 * ��ѡ��״̬���ٰ�һ��ȡ��ѡ��
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