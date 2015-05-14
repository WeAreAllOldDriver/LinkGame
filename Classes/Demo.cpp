#include "Demo.h"
#include "GameLayer.h"
#include "gameTime.h"
demoLayer* demoLayer::create(gameLayer* g)
{
	demoLayer* pRet = new demoLayer();
	if (pRet && pRet->init(g)){
		pRet->autorelease();
	}
	else{
		delete pRet;
		pRet = nullptr;
	}
	return pRet;
}

bool demoLayer::init(gameLayer* g)
{
	bool bRet = false;
	do
	{

		CC_BREAK_IF(!Layer::init());
		_gameLayer = g;
		//创建一个背景层
		auto background = LayerColor::create(Color4B(20, 162, 212, 30));
		this->addChild(background);

		auto winSize = Director::getInstance()->getWinSize();

		//title
		auto title = Sprite::create("title.png");
		title->setPosition(Point(winSize.width / 2, winSize.height / 2 + 100));
		this->addChild(title);
		//创建一个开始按钮
		auto start = MenuItemImage::create("start.png", "start.png", CC_CALLBACK_1(demoLayer::onButtonStart, this));
		start->setAnchorPoint(Point(0.5, 0.5));
		start->setPosition(Point(winSize.width / 2, winSize.height / 2));
		auto menu = Menu::createWithItem(start);
		menu->setPosition(Point::ZERO);
		background->addChild(menu);
		
		_gameLayer->createNodes();
		startDemo();
		schedule(schedule_selector(demoLayer::linkUpdate), 1.0);
	//	startDemo();
		auto touch = EventListenerTouchOneByOne::create();
		touch->onTouchBegan = [](Touch* pTouch, Event* pEvent){
			return true;
		};
		touch->setSwallowTouches(true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touch, this);
		bRet = true;
	} while (0);
	return bRet;
}

void demoLayer::OnEnter()
{
	Layer::onEnter();
	
}
void demoLayer::onButtonStart(Object* pSender)
{
	this->unschedule(schedule_selector(demoLayer::linkUpdate));
	auto winSize = Director::getInstance()->getWinSize();
	auto action1 = MoveBy::create(0.2, Point(0, -25));
	auto action2 = MoveBy::create(0.5, Point(0, winSize.height + 200));
//	auto gamelayer = this->getParent();
	auto action3 = CCCallFunc::create(this, callfunc_selector(demoLayer::startGame)); 
	auto seq = Sequence::create(action1, action2, action3, NULL);
		//CCCallFunc::create(this, callfunc_selector(demoLayer::removeFromParent)), NULL);
	this->runAction(seq);

}

void demoLayer::startDemo()
{
	
	//遍历图， 将相同种类的压进栈
	for (int i = 0; i < 7; ++i)
		ItemWithColor.push_back(new Vector<nodeItem*>);
	
	auto items = _gameLayer->_items;
	for (int i = 0; i < MAX_COL; ++i){
		for (int j = 0; j < MAX_ROW; ++j){
			if (items[i][j]){
				ItemWithColor.at(items[i][j]->getType()-1)->pushBack(items[i][j]);
			}
		}
	}
	
}

void demoLayer::linkUpdate(float dt)
{
	CCLOG("start update %f", dt);
	nodeItem *item1, *item2;
	Vector<nodeItem*>::iterator  iti, itj;
	while (itemsNumber){
		for (auto eachColor : ItemWithColor){
			if (eachColor->empty())
				continue;

			CCLOG("now find");
			/*
			for (int i = 0; i < eachColor->size(); ++i){
			CCLOG("item1: %d", i);
			item1 = eachColor->at(i);
			if (!item1)
			continue;

			_gameLayer->_lastSelectedItem = item1;
			for (int j = i + 1; j < eachColor->size(); ++j){
			CCLOG("item2: %d", j);
			item2 = eachColor->at(j);
			if (!item2)
			continue;

			if (item1 != item2 && _gameLayer->canLink(item1, item2)){
			item1->selectNode();
			item2->selectNode();
			_gameLayer->doWhenLink(item2);
			itemsNumber -= 2;
			eachColor->erase(i);
			eachColor->erase(j);
			return;
			}
			else{
			//item1->cancelNode();
			_gameLayer->_lastSelectedItem = nullptr;
			//CCLOG("link wrong! cancel");
			}
			}
			}*/
			for (iti = eachColor->begin(); iti != eachColor->end(); ++iti){
				item1 = *iti;
				CCLOG("item1: (%d, %d)", item1->getPosInMatrix().x, item1->getPosInMatrix().y);

				_gameLayer->_lastSelectedItem = item1;
				for (itj = iti + 1; itj != eachColor->end(); ++itj){
					item2 = *itj;
					//CCLOG("item2: %d", j);
					CCLOG("item2: (%d, %d)", item2->getPosInMatrix().x, item2->getPosInMatrix().y);
					if (item1 != item2 && _gameLayer->canLink(item1, item2)){
						item1->selectNode();
						item2->selectNode();
						_gameLayer->doWhenLink(item2);
						itemsNumber -= 2;
						eachColor->eraseObject(item1);
						eachColor->eraseObject(item2);
						return;
					}
				}
			}
		}
	}
	restart();
	
}

void demoLayer::restart()
{
	Layer* a = nullptr;
	_gameLayer->OnButtonAgain(a);
	itemsNumber = 100;
	startDemo();
	gameTimer::getInstance()->reset();
}

void demoLayer::startGame()
{
	_gameLayer->startGame();
	
}