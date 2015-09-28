
#include "RandomRunRole.h"

using namespace tds;
USING_NS_CC;

RandomRunRole::RandomRunRole(std::string name)
:Role(name)
{

}

bool RandomRunRole::init(std::string name)
{
	bool ret = false;
	do{

		auto path = getPath();
		if (!path.empty())
			this->initWithFile(path);
		else
			return ret;

		this->scheduleUpdate();
		ret = true;
	} while (0);

	return ret;
}

void RandomRunRole::update(float dt)
{
	this->beginRandomRun();
}

void RandomRunRole::beginRandomRun()
{
	if (this->m_CanRun)
	{
		this->m_CanRun = false;
		//Connect(Vec2());
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto pX = origin.x + (visibleSize.width * 1.5) * CCRANDOM_0_1();
		auto pY = origin.y + (visibleSize.height * 1.5) * CCRANDOM_0_1();

		auto srcPosition = this->getPosition();
		auto distance = srcPosition.getDistance(Vec2(pX, pY));
		auto moveDuration = distance / 30;


		//auto direct = (Vec2(pX, pY) - srcPosition).getNormalized();
		//Vec2 moveSpeed = direct * 2;

		//Vec2 expectP = srcPosition + moveSpeed;

		auto moveAction = Sequence::create(MoveTo::create(moveDuration, Vec2(pX, pY)),
			CallFunc::create(std::bind(&RandomRunRole::onMoveCallBack, this)),
			NULL);

		this->runAction(moveAction);

	}
}

void RandomRunRole::onMoveCallBack()
{
	this->m_CanRun = true;
}