
#include "CircleMoveAction.h"


using namespace tds;

CircleMoveAction* CircleMoveAction::create(float t, cocos2d::Point circleCenter, float radius)
{
	CircleMoveAction* circleAction = new CircleMoveAction();
	circleAction->init(t,circleCenter,radius);
	circleAction->autorelease();
	return circleAction;
}
    
bool CircleMoveAction::init(float t, cocos2d::Point circleCenter, float radius)
{
	bool ret = false;
	if (ActionInterval::initWithDuration(t))
	{
		m_center = circleCenter;
		m_radius = radius;
		m_radian = 2.0f * M_PI / (t/Director::getInstance()->getAnimationInterval());
		m_moveTimes = 1;
		ret = true;
	}
	return ret;
}

void CircleMoveAction::update(float dt)
{
	
	float radian = m_radian * m_moveTimes;

	float x = m_radius * sin(radian);
	float y = m_radius * cos(radian);

	Point newPoint = Point(x + m_center.x, y+m_center.y);

	_target->setPosition(newPoint);

	++m_moveTimes;

	log("%f", m_moveTimes);

}