
#include "RandomRunRole.h"
#include "CircleMoveAction.h"
#include "GameManager.h"

using namespace tds;
USING_NS_CC;

RandomRunRole::RandomRunRole(std::string name)
:Role(name),
m_CanRun(true)
{
	
}

bool RandomRunRole::init(std::string name)
{
	bool ret = false;
	do{

		auto path = getPath();
		if (!path.empty()){

			this->initWithFile(path);
			//auto target = Sprite::create(path);
			//target->setPosition(200.0f,200.0f);
			//this->addChild(target,0,1);

		}
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
	checkCollision();
}

void RandomRunRole::checkCollision()
{
	if (this->isVisible() && this->getOpacity()> 20)
		g_GameManager->checkCollision(this);
}

void RandomRunRole::beginRandomRun()
{
	if (this->m_CanRun)
	{
		this->m_CanRun = false;
		//Connect(Vec2());
		//
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto pX = origin.x + (visibleSize.width  ) * CCRANDOM_0_1();
		auto pY = origin.y + (visibleSize.height ) * CCRANDOM_0_1();

		

		auto srcPosition = this->getPosition();
		auto distance = srcPosition.getDistance(Vec2(pX, pY));
		auto moveDuration = distance / 30;

		//auto direct = (Vec2(pX, pY) - srcPosition).getNormalized();
		//Vec2 moveSpeed = direct * 2;

		//Vec2 expectP = srcPosition + moveSpeed;

		auto moveAction = MoveTo::create(moveDuration, Vec2(pX, pY));
		//	CallFunc::create(std::bind(&RandomRunRole::onMoveCallBack, this)),
		//	NULL);
		//auto  circleto = CircleMoveAction::create(20, srcPosition, 100);
		auto s = Director::getInstance()->getWinSize();

		auto array = PointArray::create(20);

		array->addControlPoint(Vec2(0, 0));
		array->addControlPoint(Vec2(pX, 0));
		array->addControlPoint(Vec2(pX, pY));
		array->addControlPoint(Vec2(0, pY));
		array->addControlPoint(Vec2(0, 0));
		auto action = CardinalSplineBy::create(20, array, 0);
		auto reverse = action->reverse();
		//auto seq1 = Sequence::create(action, CallFunc::create(std::bind(&RandomRunRole::onMoveCallBack, this)),
		//	NULL);
		auto seq2 = Sequence::create(moveAction, CallFunc::create(std::bind(&RandomRunRole::onMoveCallBack, this)),
			NULL);
		//this->runAction(seq1);
		this->runAction(seq2);

	}
}

void RandomRunRole::onMoveCallBack()
{
	this->m_CanRun = true;
}