#include "nodeItem.h"
#include <random>

nodeItem* nodeItem::create(const std::string& normal, const std::string& selected)
{
	nodeItem* pRet = new nodeItem();
	if (pRet && pRet->init(normal, selected))
	{
		pRet->autorelease();
	}
	else{
		delete(pRet);
		pRet = nullptr;
	}
	return pRet;
}
/*
nodeItem* nodeItem::create(Vector<std::string&> strs)
{
	nodeItem* pRet = new nodeItem();
	auto str1 = strs.at(0);
	auto str2 = strs.at(1);

	if (pRet && pRet->init(str1, str2))
	{
		pRet->autorelease();
	}
	else{
		delete(pRet);
		pRet = nullptr;
	}
	return pRet;
}
*/
nodeItem* nodeItem::randomCreate()
{
	
//	int type = u(e) + 1;
	char buf1[100], buf2[100];
	//sprintf_s(buf1, "item_%d_normal.jpg", type);
//	sprintf_s(buf2, "item_%d_selected.jpg", type);
	return  create(buf1, buf2);
	
}

nodeItem* nodeItem::createByType(int type)
{
	char buf1[100], buf2[100];
	sprintf(buf1, "item_%d_normal.jpg", type);
	sprintf(buf2, "item_%d_selected.jpg", type);
	
	return  create(buf1, buf2);
}
bool nodeItem::init(const std::string& normal, const std::string& selected)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());

		sscanf(normal.c_str(), "item_%d_normal.jpg", &_nodeType);
		_normalImage = Sprite::create(normal);
		_normalImage->setAnchorPoint(Point(0.5, 0.5));
		_normalImage->setPosition(_normalImage->getContentSize().width/2,
			_normalImage->getContentSize().height/2);
		_normalImage->setVisible(true);
	//	_normalImage->retain();
		this->addChild(_normalImage);

		_selectedImage = Sprite::create(selected);
		_selectedImage->setAnchorPoint(Point(0.5, 0.5));
		_selectedImage->setPosition(_normalImage->getContentSize().width / 2,
			_normalImage->getContentSize().height / 2);
		_selectedImage->setVisible(false);
	//	_selectedImage->retain();
		this->addChild(_selectedImage);

		_currentState = nodeState::NORMAL;

		bRet = true;
	} while (0);
	return bRet;
}

void nodeItem::selectNode()
{
	if(_currentState == nodeState::NORMAL)
	{
		_currentState = nodeState::SELECTED;
		_normalImage->setVisible(false);
		_selectedImage->setVisible(true);
		CCLOG("node select!");
		return;
	}
	CCLOG("select error! wrong state");
	
}

void nodeItem::cancelNode()
{
	if (_currentState == nodeState::SELECTED)
	{
		_currentState = nodeState::NORMAL;
		_selectedImage->setVisible(false);
		_normalImage->setVisible(true);
		CCLOG("node unselect!");
		return;
	}
	CCLOG("cancal error! wrong state");
}

void nodeItem::removeNode()
{
//	if (_currentState == nodeState::SELECTED)
	//{
	auto rotate = RotateBy::create(0.5, 180);
	auto scale = ScaleBy::create(0.5, 1.5);
	auto disappear = FadeOut::create(0.5);
	auto spawn = Spawn::create(scale, disappear, NULL);
	auto action = Sequence::create(rotate, spawn, 
		CCCallFunc::create(this, callfunc_selector(nodeItem::removeFromParent)), NULL);
	_selectedImage->runAction(action);
	CCLOG("REMOVE X=%f, y=%f", this->getPosition().x, this->getPosition().y);
//	this->removeFromParent();
	CCLOG("node remove!");
//	}
//	CCLOG("remove error!");
}

Rect nodeItem::rect() const
{
	auto pos = _normalImage->convertToWorldSpace(_normalImage->getPosition());
	auto size = _normalImage->getContentSize();
	auto anthor = _normalImage->getAnchorPoint();

	return Rect(pos.x - size.width * anthor.x,
		pos.y - size.height * anthor.y,
		size.width,
		size.height);
}

void nodeItem::changeType(int type)
{
	char buf1[100], buf2[100];
	sprintf(buf1, "item_%d_normal.jpg", type);
	sprintf(buf2, "item_%d_selected.jpg", type);

	auto tex1 = Director::getInstance()->getTextureCache()->addImage(buf1);
	auto tex2 = Director::getInstance()->getTextureCache()->addImage(buf2);

	_normalImage->setTexture(tex1);
	_selectedImage->setTexture(tex2);

	_nodeType = type;
}