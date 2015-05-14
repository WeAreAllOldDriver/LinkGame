#include "GameLayer.h"
#include <random>
#include <ctime>
#include "lineViewer.h"
#include "Score.h"

#define ABS(i) (((i) > 0) ? (i) : -1 * (i))

Scene* gameLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = gameLayer::create();

	if (scene && layer)
	{
		scene->addChild(layer);
	}
	return scene;
}

bool gameLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		for (int i = 0; i < 10; ++i)
			for (int j = 0; j < 10; ++j)
				_items[i][j] = nullptr;

		auto background = LayerColor::create(Color4B(255, 255, 255, 255));
		this->addChild(background);
		auto winSize = Director::getInstance()->getWinSize();

	//	createNodes();

	 	//restart
		auto restart = MenuItemImage::create("restart1.png", "restart1.png", CC_CALLBACK_1(gameLayer::onButtonRestart, this));
		restart->setAnchorPoint(Point(0, 1));
		restart->setPosition(Point(40, winSize.height-20));
		auto menu = Menu::createWithItem(restart);
		menu->setPosition(Point::ZERO);
		this->addChild(menu);

		//touch
		auto touch = EventListenerTouchOneByOne::create();
		touch->onTouchBegan = CC_CALLBACK_2(gameLayer::OnTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touch, this);

		//连接线
		auto drawline = lineViewer::getInstance();
		this->addChild(drawline, 4);

		//显示当前屏幕分辨率
		char bufWidth[100];
		char bufHeight[100];
		sprintf(bufWidth, "Width: %.0f", winSize.width);
		sprintf(bufHeight, "Height: %.0f", winSize.height);
		auto label1 = Label::create(bufWidth, "Marker Felt", 20);
		auto label2 = Label::create(bufHeight, "Marker Felt", 20);
		label1->setAnchorPoint(Point(1, 1));
		label2->setAnchorPoint(Point(1, 1));
		label1->setPosition(Point(winSize.width, winSize.height));
		label2->setPosition(Point(winSize.width, winSize.height - label1->getContentSize().height));
		label1->setColor(Color3B::BLACK);
		label2->setColor(Color3B::BLACK);

		this->addChild(label1);
		this->addChild(label2);

		//set 计时器
		_timer = gameTimer::getInstance();
		_timer->setPosition(Point(7 * winSize.width / 8 - 40, label2->getPosition().y - 100));
		this->addChild(_timer);
		//set init state
		_state = gameState::DEMO;

		//score display
		auto score = ScoreDisplay::getInstance();
		score->setPosition(Point(winSize.width / 2,
			winSize.height - score->getImageSize().height / 2));
		
		this->addChild(score);

		_itemsRemain = 100;

		//再来一次
		_againBtn = MenuItemFont::create("AGAIN!", CC_CALLBACK_1(gameLayer::OnButtonAgain, this));
		_againBtn->setAnchorPoint(Point(0, 1));
		_againBtn->setPosition(Point(winSize.width / 2 - 30, 50));
		_againBtn->setColor(Color3B::BLACK);
		_againBtn->setEnabled(false);
		_againBtn->setDisabledColor(Color3B::WHITE);

		_againMenu = Menu::createWithItem(_againBtn);
		_againMenu->setPosition(Point::ZERO);
		_againMenu->setVisible(false);
		//_againMenu->setEnabled(false);
		this->addChild(_againMenu);

		//开始界面
		_demo = demoLayer::create(this);
		_demo->setName("start");
		this->addChild(_demo, 10);

		//加入一个动画
		auto framecache = SpriteFrameCache::getInstance();
		framecache->addSpriteFramesWithFile("loli1.plist");
		/*
		auto cache = AnimationCache::getInstance();
		cache->addAnimationsWithFile("loli1.plist");
		auto ani = cache->getAnimation("loli1.plist");
		ani->retain();
		auto animate = Animate::create(ani);
		*/
		
		Vector<SpriteFrame*> animations;
		char str[100] = { 0 };
		for (int i = 1; i <= 27; ++i)
		{
			sprintf(str, "loli_0%02d.jpg", i);
			auto frame = framecache->getSpriteFrameByName(str);
			animations.pushBack(frame);
		}
		auto animation = Animation::createWithSpriteFrames(animations, 0.1f);
		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		auto loli = Sprite::create();
		loli->setDisplayFrame(animations.at(0));

		loli->setPosition(Point(winSize.width / 8, winSize.height / 2));
		loli->runAction(action);
		this->addChild(loli);
		
		_lastSelectedItem = nullptr;
		bRet = true;
	} while (0);
	return bRet;
}

void gameLayer::onButtonRestart(Object* Sender)
{
	std::vector<iPoint> currentItems;
	std::uniform_int_distribution<unsigned> u(0, 6);//生成0到5（包含）均匀分布的随机数
	std::default_random_engine e(std::time(0));
	int lastType;
	bool next = false;
	for (int i = 0; i < MAX_COL; ++i){
		for (int j = 0; j < MAX_ROW; ++j){
			if (_items[i][j] == nullptr)
				continue;
			else{
				iPoint pos(j, i);
				currentItems.push_back(pos);
			}
			int type;
			if (next == false)
			{
				type = u(e) + 1;
				lastType = type;
				next = true;
			}
			else
			{
				type = lastType;
				next = false;
			}

			if (_items[i][j])
				_items[i][j]->changeType(type);
		}
	}
	//打散
	std::uniform_int_distribution<unsigned> v(0, 9);
	for (int i = 0; i < MAX_COL; ++i){
		for (int j = 0; j < MAX_ROW; ++j){
			iPoint nextItem;
			if (_items[i][j] == nullptr)
				continue;
			else{ //随机访问
				ssize_t randIdx = rand() % currentItems.size();
				nextItem =  *(currentItems.begin() + randIdx);
			}
				
			auto x = nextItem.y;
			auto y = nextItem.x;
			if (_items[x][y] != nullptr){//交换两个item的坐标
				auto temp = _items[i][j];
				_items[i][j] = _items[x][y];
				_items[x][y] = temp;

				//iPoint pos1, pos2;
				//	pos1 = _items[i][j]->getPosInMatrix();
				//	pos2 = _items[x][y]->getPosInMatrix();
				auto pos = _items[i][j]->getPosition();
				_items[i][j]->setPosition(_items[x][y]->getPosition());
				_items[x][y]->setPosition(pos);

				//	_items[i][j]->setPosInMatrix(pos2);
				//	_items[x][y]->setPosInMatrix(pos1);
			}
		}
	}
	for (int i = 0; i < MAX_COL; ++i){
		for (int j = 0; j < MAX_ROW; ++j){
			if (_items[i][j]){
				iPoint pos = iPoint(j, i);
				_items[i][j]->setPosInMatrix(pos);
			}
		}
	}
}
bool gameLayer::OnTouchBegan(Touch* pTouch, Event* pEvent)
{
	_selectedItem = getItemForTouch(pTouch);
	if (_selectedItem){
		CCLOG("on TouchBegan!");
		/*
		auto state = _selectedItem->getCurrentState();
		switch (state)
		{
			case nodeItem::nodeState::NORMAL:
				_selectedItem->selectNode();
				break;
			case nodeItem::nodeState::SELECTED:
				_selectedItem->cancelNode();
				break;
		}*/
		progressItem(_selectedItem);
		return true;	
	}
	return false;
}

//游戏逻辑处理
void gameLayer::progressItem(nodeItem* item)
{
	if (_lastSelectedItem == item
		&& item->getCurrentState() == nodeItem::nodeState::SELECTED)
	{
		_lastSelectedItem = nullptr;
		item->cancelNode();
	}
	else
	{
		if (_lastSelectedItem == nullptr) {//没有
			_lastSelectedItem = item;
			item->selectNode();
			CCLOG("Select it");
			return;
		}
		else
		{
			if (_lastSelectedItem->getType() == item->getType())
			{
				if (canLink(item, _lastSelectedItem)) //两个item可以按规则消除
				{
				//	lineViewer::getInstance()->clearLines();
					doWhenLink(item);
					//是否全部消除

				}
				else
				{
					_lastSelectedItem->cancelNode();
					_lastSelectedItem = nullptr;
					CCLOG("link wrong! cancel");
				}
			}
			else
			{
				_lastSelectedItem->cancelNode();
				_lastSelectedItem = nullptr;
				CCLOG("link wrong! cancel");
			}
		}
	}
}

void gameLayer::doWhenLink(nodeItem* item)
{
	ScoreDisplay::getInstance()->addProgress();
	_itemsRemain -= 2;
	lineViewer::getInstance()->showDirection();
	item->selectNode();
	CCLOG("remove! 1:(%d, %d) 2:(%d, %d)", item->getPosInMatrix().y, item->getPosInMatrix().x
		, _lastSelectedItem->getPosInMatrix().y, _lastSelectedItem->getPosInMatrix().x);

	_items[(int)item->getPosInMatrix().y][(int)item->getPosInMatrix().x] = nullptr;
	auto p = _lastSelectedItem->getPosInMatrix();
	_items[(int)p.y][(int)p.x] = nullptr;

	_lastSelectedItem->removeNode();
	item->removeNode();

	_lastSelectedItem = nullptr;
	CCLOG("both two node have been delete!");
	DelayTime* action;
	if (_state == gameState::DEMO)
		action = CCDelayTime::create(1.0f);
	else
		action = CCDelayTime::create(0.5f);
	this->runAction(action);
	
	if (_itemsRemain == 0)
	{
		_state = gameState::GAMEOVER;
		_againBtn->setEnabled(true);
		_againMenu->setVisible(true);
		gameTimer::getInstance()->stop();
	}

}
//两个node是否可以消除
bool gameLayer::canLink(nodeItem* a, nodeItem* b)
{
	//第一种，可以用一条直线相连
	iPoint pos1 = a->getPosInMatrix();
	iPoint pos2 = b->getPosInMatrix();
//	CCLOG("pos1.x = %d, pos1.y=%d", pos1.x, pos1.y);
//	CCLOG("pos2.x = %d, pos2.y=%d", pos2.x, pos2.y);
	if (isLinkDirect(pos1, pos2)){ //两个item处于一直线上
		drawLine(pos1, pos2);

		return 1;
	}
	else if (isLinkByTwoLine(pos1, pos2))//两个item可以用两条直线连接
		return 1;
	else if (isLinkByThreeLine(pos1, pos2))
		return 1;
	return false;

}

bool gameLayer::isLinkByTwoLine(iPoint a, iPoint b)
{
	//若两点(x1,y1) (x2,y2)能用两条线连接
	//则转折点为(x1,y2) or (x2,y1)
	iPoint a1(a.x, b.y), a2(b.x, a.y);
	if (isLinkDirect(a, a1) && isLinkDirect(a1, b)){
	//	CCLOG("a1.x = %d, a1.y=%d", a1.x, a1.y);
		if (_items[a1.y][a1.x] == nullptr){
			drawLine(a, a1);
			drawLine(a1, b);
			return 1;
		}
	}
	if (isLinkDirect(a, a2) && isLinkDirect(a2, b)){
	//	CCLOG("a2.x = %d, a2.y=%d", a2.x, a2.y);
		if (_items[a2.y][a2.x] == nullptr){
			drawLine(a, a2);
			drawLine(a2, b);
			return 1;
		}
	}
	return 0;
}
bool gameLayer::isLinkByThreeLine(iPoint a, iPoint b)
{
	iPoint a1, b1;
	//纵向扫描
	a1.y = a.y;
	b1.y = b.y;
	for (int i = -1; i <= MAX_COL; ++i)
	{
		a1.x = b1.x = i;
		if (isLinkDirect(a, a1) && isLinkDirect(a1, b1) && isLinkDirect(b1, b)){
			if (isEmpty(a1) && isEmpty(b1)){
				drawLine(a, a1);
				drawLine(a1, b1);
				drawLine(b1, b);
				return 1;
			}
		}
	}
	a1.x = a.x;
	b1.x = b.x;
	for (int i = -1; i <= MAX_ROW; ++i)
	{
		a1.y = b1.y = i;
		if (isLinkDirect(a, a1) && isLinkDirect(a1, b1) && isLinkDirect(b1, b)){
			if (isEmpty(a1) && isEmpty(b1)){
				drawLine(a, a1);
				drawLine(a1, b1);
				drawLine(b1, b);
				return 1;
			}
		}
	}
	return 0;
}
//isEmpty:判断该位置是否为空
//第一种是为nullptr 另一种为超出矩阵边界
bool gameLayer::isEmpty(int i, int j)
{
	if (_items[i][j] == nullptr)
		return 1;
	else if (i < 0 || j < 0 || i >= MAX_ROW || j >= MAX_COL)
		return 1;
	else
		return 0;
}

bool gameLayer::isEmpty(iPoint a)
{
	return isEmpty(a.y, a.x);
}
//越界
bool gameLayer::isOutOfMatrix(iPoint a)
{
	if (a.x >= 0 && a.x < MAX_COL
		&& a.y >= 0 && a.y < MAX_ROW)
		return 0;
	return 1;

}
//两个node是否能直连 最后一个参数为是否为水平直连
bool gameLayer::isLinkDirect(iPoint a, iPoint b)
{
	
	int direction = -1;
	//int flag = 1;
	/*
	if (!isOutOfMatrix(a) && !isOutOfMatrix(b))//越界
		flag = 0;
	else
		flag = 1;
	*/
	iPoint up, down, left, right;
	
	if (a.x == b.x){//竖直
		direction = 1;
		if (a.y < b.y){
			down = a;
			up = b;
		}
		else{
			down = b;
			up = a;
		}
	}
	else if (a.y == b.y){
		direction = 0;
		if (a.x < b.x){
			left = a;
			right = b;
		}
		else{
			left = b;
			right = a;
		}
	}
	if (direction != -1)
	{
		if (direction == 1)
		{
			for (int i = down.y + 1; i < up.y; ++i)
			{
				if (!isEmpty(i, down.x))
					return 0;
			}
		}
		else if (direction == 0)
		{
			for (int i = left.x + 1; i < right.x; ++i)
			{
				if (!isEmpty(left.y, i))
					return 0;
			}
		}
		return 1;
	}
	/*
	if (direction != -1)
	{
		if (flag == 0)
		{
			if (direction == 1){//竖直
				CCLOG("%d", ABS(a.y - b.y));
				//if (ABS(a.y - b.y) == 1)
				//	return 1;
				auto up = a.y > b.y ? b : a;
				for (int i = 0; i < (ABS(a.y - b.y)) - 1; ++i){
					//if (_items[i + 1 + up.y][up.x] != nullptr)
					if (!isEmpty(i + 1 + up.y, up.x))
						return 0;
				}return 1;
			}
			else if (direction == 0)
			{
				//if (ABS(a.x - b.x) == 1)
				//	return 1;
				CCLOG("%d", ABS(a.x - b.x));

				auto left = a.x < b.x ? a : b;
				for (int i = 0; i < (ABS(a.x - b.x)) - 1; ++i){
					//if (_items[left.y][i + 1 + left.x] != nullptr)
					if (!isEmpty(left.y, i + 1 + left.x))
						return 0;
				}
				return 1;
			}
		}
		else //有一个点越界了
		{
			if (direction == 1){
				iPoint up, down;
				if (isOutOfMatrix(a)){
					up = a; down = b;
				}else {
					up = b; down = a;
				}
				for (int i = down.y + 1; i < MAX_ROW; ++i){
					if (!isEmpty(i, down.x))
						return 0;
				}
				return 1;
			}
			else if (direction == 0){ 
			}
		}
	}*/
	return 0;
}


nodeItem* gameLayer::getItemForTouch(Touch* touch)
{
	auto pos = touch->getLocation();
	nodeItem* choosed = nullptr;
	float maxZ = -999;
	
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j){
			auto unit = _items[i][j];
			if (unit){
				auto local = unit->convertToNodeSpace(pos);
				Rect r = unit->rect();
				r.origin = Point::ZERO;
				if (r.containsPoint(local))
				{
					if (maxZ < unit->getItemZPosition()){
						maxZ = unit->getItemZPosition();
						choosed = unit;
					}
				}
			}
		}
	
	return choosed;
}

/*
void gameLayer::createNodes()
{
	std::uniform_int_distribution<unsigned> u(0, 6);//生成0到5（包含）均匀分布的随机数
	std::default_random_engine e(std::time(0));
	for (int i = 0; i < MAX_COL; ++i){
		for (int j = 0; j < MAX_ROW; ++j){
			//auto names = randomImageName();
			//auto node = nodeItem::randomCreate();
			int type = u(e) + 1;

			auto node = nodeItem::createByType(type);
			//auto node = nodeItem::create("item_1_normal.jpg", "item_1_selected.jpg");
			auto nodeSize = node->getImageSize();
			auto winSize = Director::getInstance()->getWinSize();
			node->setPosition(200 + j * nodeSize.width + 5, 50 + i * nodeSize.height + 5);
			_items[i][j] = node;
			iPoint pos = iPoint(j, i);
			node->setPosInMatrix(pos);
			this->addChild(node);
		}
	}
	
}*/

void gameLayer::createNodes()
{
	std::uniform_int_distribution<unsigned> u(0, 6);
	std::default_random_engine e(std::time(0));
	//创建图 第二个位置与第一个位置相同 然后随机打散
	bool next = false;
	int lastType = 0;
	auto winSize = Director::getInstance()->getWinSize();
	auto left_bottom = Point(winSize.width / 2 - MAX_COL / 2.0 * 50,//item的长宽
		winSize.height/2 - MAX_COL / 2.0 * 50);
	for (int i = 0; i < MAX_COL; ++i){
		for (int j = 0; j < MAX_ROW; ++j){
			int type;
			if (next == false)
			{
				type = u(e) + 1;
				lastType = type;
				next = true;
			}
			else
			{
				type = lastType;
				next = false;
			}
			auto node = nodeItem::createByType(type);
			auto nodeSize = node->getImageSize();
			
			node->setPosition(left_bottom.x + j * nodeSize.width + 5, left_bottom.y + i * nodeSize.height + 5);
			_items[i][j] = node;
			node->retain(); 
			//iPoint pos = iPoint(j, i);
			//node->setPosInMatrix(pos);
			this->addChild(node);
		}
	}
	
	//打散
	std::uniform_int_distribution<unsigned> v(0, 9) ;
	for (int i = 0; i < MAX_COL; ++i){
		for (int j = 0; j < MAX_ROW; ++j){
			int x = v(e);
			int y = v(e);
			if (_items[x][y] != nullptr){//交换两个item的坐标
				auto temp = _items[i][j];
				_items[i][j] = _items[x][y];
				_items[x][y] = temp;



				//iPoint pos1, pos2;
			//	pos1 = _items[i][j]->getPosInMatrix();
			//	pos2 = _items[x][y]->getPosInMatrix();
				auto pos = _items[i][j]->getPosition();
				_items[i][j]->setPosition(_items[x][y]->getPosition());
                _items[x][y]->setPosition(pos);

			//	_items[i][j]->setPosInMatrix(pos2);
			//	_items[x][y]->setPosInMatrix(pos1);
			}
		}
	}
	for (int i = 0; i < MAX_COL; ++i){
		for (int j = 0; j < MAX_ROW; ++j){
			iPoint pos = iPoint(j, i);
			_items[i][j]->setPosInMatrix(pos);
		}
	}

	//保存第一个item的位置
	_firstItemPosition = _items[0][0]->getPosition();
	_firstItemSize = _items[0][0]->getImageSize(); 
	_firstItemPosition.x += _firstItemSize.width / 2;
	_firstItemPosition.y += _firstItemSize.height / 2;

	_itemsRemain = MAX_COL * MAX_ROW;
}

void gameLayer::drawLine(iPoint a, iPoint b)
{

	Point p1, p2;
	p1.x = _firstItemPosition.x + a.x * _firstItemSize.width;
	p1.y = _firstItemPosition.y + a.y * _firstItemSize.height;

	p2.x = _firstItemPosition.x + b.x * _firstItemSize.width;
	p2.y = _firstItemPosition.y + b.y * _firstItemSize.height;
	auto pos1 = this->convertToWorldSpace(p1);
	auto pos2 = this->convertToWorldSpace(p2);

	lineViewer::getInstance()->addLine(pos1, pos2);
}

//重新开始游戏
void gameLayer::OnButtonAgain(Object* pSender)
{
	_state = gameState::START;
	_itemsRemain = 100;
	createNodes();
	ScoreDisplay::getInstance()->reset();
	_againMenu->setVisible(false);
	_againBtn->setEnabled(false);
	_timer->reset();
	_timer->start();
}

void gameLayer::startGame()
{
	_state = gameState::START;
	_selectedItem = nullptr;
	Layer* a = nullptr;
	//删除已存在的item
	for (int i = 0; i < MAX_COL; ++i){
		for (int j = 0; j < MAX_ROW; ++j){
			if (_items[i][j]){
				_items[i][j]->removeFromParent();
				_items[i][j] = nullptr;
			}
		}
	}

	OnButtonAgain(a);

	_demo->removeFromParent();
	gameTimer::getInstance()->reset();
}