
#include "LeadingMan.h"
#include "RoleEnergyPoints.h"
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
	//printf("%s", __func__);
}

bool LeadingMan::init()
{
	bool ret = false;
	do{
		this->initWithSpriteFrameName("L4_00.png");
		
		Animation *L1 = Role::CreateNormalAnimation("Level1_new_%02d.png",5,1);
		this->setL1Action(RepeatForever::create(Animate::create(L1)));

		Animation *L2 = Role::CreateNormalAnimation("L5_%02d.png",1, 10);
		this->setL2Action(RepeatForever::create(Animate::create(L2)));

		Animation *L3 = Role::CreateNormalAnimation("L6_%02d.png",1, 10);
		this->setL3Action(RepeatForever::create(Animate::create(L3)));

		Animation *L4 = Role::CreateNormalAnimation("L4_%02d.png",1, 10);
		this->setL4Action(RepeatForever::create(Animate::create(L4)));

		this->setAnchorPoint(Vec2(0.0f,0.5f));

		ret = true;
	} while (0);
	return ret;
}

void LeadingMan::updateSelf(float duration)
{
	Vec2 currentP = this->getPosition();
	Vec2 expectP = currentP + this->getVelocity();
	Vec2 actualP = expectP;
	auto moveto = MoveTo::create(duration, actualP);
	this->runAction(moveto);
	auto r = this->getContentSize().width / 2;
	auto sita = this->getRotation();
	auto nol = Vec2(sin(sita),cos(sita));
	for (auto hp : _kHPVector){
		auto no = -this->getLastVelocity().getNormalized();
		auto v = Vec2( this->getContentSize().width*no,
			this->getContentSize().height*no);
		hp->setPosition(this->getPosition() - v);
	}
	//this->setPosition(actualP);
}