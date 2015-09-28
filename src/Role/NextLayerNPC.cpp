
#include "NextLayerNPC.h"
using namespace tds;
USING_NS_CC;

NextLayerNPC::NextLayerNPC()
:Role("NextLayerNPC"),
m_UpdateTimer(true),
m_NextMoveTime(0)
{

}

NextLayerNPC::~NextLayerNPC()
{

}

bool NextLayerNPC::init()
{
	bool ret = false;

	do{
		this->initWithFile("NextLayerNPC.png");
		this->scheduleUpdate();

		m_DrawSignal = DrawNode::create();
		this->addChild(m_DrawSignal);

		ret = true;
	} while (0);

	return ret;
}

void NextLayerNPC::update(float dt)
{

	if (m_UpdateTimer)
	{
		m_UpdateTimer = false;
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

		auto moveAction = Sequence::create(MoveTo::create(moveDuration,Vec2(pX,pY)),
			CallFunc::create(std::bind(&NextLayerNPC::onMoveCallBack, this)),
			NULL);

		this->runAction(moveAction);

		
	}
}

void NextLayerNPC::onMoveCallBack()
{
	m_UpdateTimer = true;
	//auto center = Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2);
	//onSignaling(center);
	//this->scheduleOnce(CC_SCHEDULE_SELECTOR(NextLayerNPC::onConnected),0.5f);

}

void NextLayerNPC::onSignaling(Point p)
{
	
	m_DrawSignal->drawCircle(p, 5, 0, 360, false, Color4F::BLUE);
	m_DrawSignal->setOpacity(122);

	auto scaleby = ScaleBy::create(1,10);
	auto action2 = Sequence::create(
		scaleby,
		FadeOut::create(1),nullptr);

	m_DrawSignal->runAction(action2);


}

/*
bool NextLayerNPC::IsOutOffPlayerVision(Vec2 p)
{
	bool ret = false;

	auto currentPosition = this->getPosition();


	return ret;
}
*/

void NextLayerNPC::Connect(cocos2d::Vec2 playerposition)
{
	auto orig = Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2);

	m_DrawSignal->drawLine(orig, m_PlayerPositon, Color4F::BLUE);
	
	scheduleOnce(CC_SCHEDULE_SELECTOR(NextLayerNPC::onConnected),1.0f);
}

void NextLayerNPC::onConnected(float dt)
{
	m_DrawSignal->clear();
}