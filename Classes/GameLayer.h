#pragma once
#include "cocos2d.h"
#include "nodeItem.h"
#include "Demo.h"
#include "gameTime.h"
USING_NS_CC;

#define MAX_ROW 10//每行最大个数
#define MAX_COL 10//每列
class demoLayer;
class gameLayer : public Layer
{
public:
	enum class gameState{
		DEMO,
		START,
		GAMEOVER
	};
	virtual bool init();
	CREATE_FUNC(gameLayer);
	static Scene* createScene();

	bool OnTouchBegan(Touch* pTouch, Event* pEvent);
	void OnTouchEnded(Touch* pTouch, Event* pEvent);
	friend class demoLayer;

	void startGame();
private:
	nodeItem* _items[MAX_ROW][MAX_COL];
	//Vector<nodeItem*> _selectedItems;
	nodeItem* _lastSelectedItem = nullptr; //上一个已选中的item
	nodeItem* _selectedItem = nullptr;
	Point _firstItemPosition;
	Size  _firstItemSize;
	gameState _state;
	Menu* _againMenu;
	MenuItemFont* _againBtn;
	demoLayer* _demo;
	int _itemsRemain; //还剩的item数
	nodeItem* getItemForTouch(Touch* touch);
	gameTimer* _timer;

	void createNodes();

	void onButtonRestart(Object* Sender);
	void OnButtonAgain(Object* pSender);
	void progressItem(nodeItem* item);

	bool canLink(nodeItem* a, nodeItem* b);
	bool isLinkDirect(iPoint a, iPoint b);
	bool isLinkByTwoLine(iPoint a, iPoint b);
	bool isLinkByThreeLine(iPoint a, iPoint b);

	bool isOutOfMatrix(iPoint a);
	bool isEmpty(int x, int y);
	bool isEmpty(iPoint a);
	void drawLine(iPoint a, iPoint b);

	void doWhenLink(nodeItem* item);
};