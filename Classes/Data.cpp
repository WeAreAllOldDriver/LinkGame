#include "Data.h"
#include "base\CCUserDefault.h"

static StaticData* sharedStaticData = nullptr;
StaticData* StaticData::getInstance()
{
	if (!sharedStaticData){
		sharedStaticData = new StaticData;
		CCASSERT(sharedStaticData, "not enough menory");
		sharedStaticData->init();
	}
	return sharedStaticData;

}

bool StaticData::init()
{
	if (_dic = CCDictionary::createWithContentsOfFileThreadSafe("static_data.plist"))
		return true;
	return false;
}

Rect StaticData::rectFromKey(std::string key)
{
	auto value = _dic->valueForKey(key);
	float x, y, width, height;
	sscanf_s(value->getCString(), "{%f,%f,%f,%f}", &x, &y,
		&width, &height);
	return Rect(x, y, width, height);
}

Vec2 StaticData::pointFromKey(std::string key)
{
	auto str = _dic->valueForKey(key);
	float x, y;
	sscanf_s(str->getCString(), "{%f,%f}", &x, &y);
	return Point(x, y);
}

Size StaticData::sizeFromKey(std::string key)
{
	auto str = _dic->valueForKey(key)->getCString();
	float width, height;
	sscanf_s(str, "{%d,%d}", &width, &height);
	return Size(width, height);
}

const char* StaticData::stringFromKey(std::string key)
{
	auto str = _dic->valueForKey(key)->getCString();
	return str;
}

int StaticData::intFromKey(std::string key)
{
	auto str = _dic->valueForKey(key)->getCString();
	int i;
	sscanf_s(str, "%d", i);
	return i;
}

float StaticData::floatFromKey(std::string key)
{
	auto str = _dic->valueForKey(key)->getCString();
	int i;
	sscanf_s(str, "%f", i);
	return i;
}

bool StaticData::booleanFromKey(std::string key)
{
	auto str = _dic->valueForKey(key)->getCString();
	bool i;
	sscanf_s(str, "%d", i);
	return i;
}

void StaticData::purge()
{
	CC_SAFE_RELEASE(this);
}

void StaticData::setIntInKey(int i, std::string key)
{
	char buffer[100];
	sprintf_s(buffer, "%d", i);
	auto str = String::create(buffer);
	_dic->setObject(str, "key");
}

void StaticData::saveToFile()
{
	std::string fullpath = FileUtils::getInstance()->fullPathForFilename("static_data.plist");
	_dic->writeToFile(fullpath.c_str());
}

Point StaticData::convertToGL(Point pos)
{
	return Director::getInstance()->convertToGL(pos);
}

Rect StaticData::convertToGL(Rect  rect)
{
	auto pos = Director::getInstance()->convertToGL(rect.origin);
	return Rect(pos.x, pos.y, rect.size.width, rect.size.height);
}