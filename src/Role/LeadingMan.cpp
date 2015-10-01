
#include "LeadingMan.h"
using namespace tds;
USING_NS_CC;

LeadingMan* LeadingMan::create(std::string name)
{
	auto ret = new (std::nothrow)LeadingMan(name);

	if (ret && ret->init() ){
		ret->autorelease();
	}
	else{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

LeadingMan::LeadingMan(std::string name)
:Role(name)
{

}

LeadingMan::~LeadingMan()
{
	printf("%s", __func__);
}

bool LeadingMan::init()
{
	bool ret = false;
	do{
		this->initWithFile("LeadingMan2.png");

		ret = true;
	} while (0);
	return ret;
}