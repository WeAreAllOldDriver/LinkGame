#pragma once
#include "cocos2d.h"
#include "base\CCNS.h"
#include "base\CCUserDefault.h"

USING_NS_CC;

#define STATIC_DATA_STRING(k)	StaticData::getInstance()->stringFromKey(k)
#define STATIC_DATA_INT(k)		StaticData::getInstance()->intFromKey(k)
#define STATIC_DATA_FLOAT(k)	StaticData::getInstance()->floatFromKey(k)
#define STATIC_DATA_RECT(k)		StaticData::getInstance()->rectFromKey(k)
#define STATIC_DATA_POINT(k)	StaticData::getInstance()->pointFromKey(k)
#define STATIC_DATA_SIZE(k)		StaticData::getInstance()->sizeFromKey(k)
#define STATIC_DATA_BOOL(k)		StaticData::getInstance()->booleanFromKey(k)
#define STATIC_DATA_POINT_CONVERTED_TO_GL(k) \
								StaticData::getInstance()->convertToGL( \
								StaticData::getInstance()->pointFromKey(k))
#define STATIC_DATA_RECT_CONVERTED(k) \
								StaticData::getInstance()->convertToGL( \
								StaticData::getInstance()->pointFromKey(k))
class StaticData :public Object
{
public: 
	static StaticData* getInstance();
	void purge();

	//in CCNS.h
	Rect rectFromKey(std::string key);
	Vec2 pointFromKey(std::string key);
	Size sizeFromKey(std::string key);
	
	const char* stringFromKey(std::string key);
	int intFromKey(std::string key);
	float floatFromKey(std::string key);
	bool booleanFromKey(std::string key);

	void setIntInKey(int i, std::string key);
	//void setPointInKey(Point point, std::string key);
	Point convertToGL(Point pos);
	Rect  convertToGL(Rect rect);
	void saveToFile();
protected:

	Dictionary* _dic;
private:
//	StaticData();
//	~StaticData();
	bool init();
};