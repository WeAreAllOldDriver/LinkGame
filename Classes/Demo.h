#pragma once
#include "cocos2d.h"
#include "nodeItem.h"
#include "GameLayer.h"
/*
 * ��ʾ��ʼ��ť������һ����Ϸdemo
 */
class gameLayer;
class demoLayer : public Layer
{
public:
	virtual bool init(gameLayer* g);
	static demoLayer* create(gameLayer* g);
	void linkUpdate(float dt);
	void startDemo();
private:
	std::vector<Vector<nodeItem*>*> ItemWithColor;

	void onButtonStart(Object* pSender);
	gameLayer* _gameLayer;
	virtual void OnEnter();
	//��ʱ��
	
	Vector<nodeItem*>* _eachcolor;
	int itemsNumber = 100;

	void restart();
	void startGame();
};