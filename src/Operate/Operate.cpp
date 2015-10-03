
#include "Operate.h"
using namespace std;
using namespace tds;
#include "GameManager.h"

Joystick::Joystick()
:m_bisTouchDown(false)
{
}

Joystick::~Joystick()
{
}

bool Joystick::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Sprite::init());
		m_pJoystickBg = Sprite::create("joystickBg.png");
		m_pJoystick = Sprite::create("joystick.png");

		m_pJoystickBg->setScale(1.4f);
		m_pJoystick->setScale(1.4f);

		this->addChild(m_pJoystickBg, 0);
		this->addChild(m_pJoystick, 1);

		this->hideJoystick();
		//this->showJoystick();
		m_pJoystickR = m_pJoystickBg->getContentSize().width / 2;
		m_pJoystickr = m_pJoystick->getContentSize().width / 2;

		ret = true;
	} while (0);

	return ret;
}

void Joystick::onEnter()
{
	Sprite::onEnter();
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(Joystick::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(Joystick::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(Joystick::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(Joystick::onTouchesCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void Joystick::onExit()
{
	Sprite::onExit();
}

void Joystick::showJoystick()
{

	m_pJoystick->setVisible(true);
	m_pJoystickBg->setVisible(true);
}

void Joystick::hideJoystick()
{

	//m_pJoystick->setPosition(m_pJoystickBg->getPosition());
	m_pJoystick->setVisible(false);
	//m_pJoystickBg->setVisible(false);
	m_pJoystickBg->setVisible(true);
}

void Joystick::updateJoystick(Touch* touch)
{
	Vec2 hit = touch->getLocation();
	float distance = start.getDistance(hit);
	Vec2 direction = (hit - start).getNormalized();

	if (distance < m_pJoystickr / 2)
	{
		m_pJoystick->setPosition(start + (direction * distance));
	}
	else if (distance >m_pJoystickr) {
		m_pJoystick->setPosition(start + (direction * m_pJoystickr));
	}
	else {
		m_pJoystick->setPosition(start + (direction * m_pJoystickr / 2));
	}
	auto rotation = atan2((hit.x - start.x),
		(hit.y - start.y)) * 180 / M_PI + 90;
	//auto rotate = RotateTo::create(0.3, rotation);

	
	g_GameManager->onPlayerMove(direction, distance);
	g_GameManager->onSPELayerMove(direction, distance);
	g_GameManager->onPlayerRotation(rotation);
}


void Joystick::onTouchesBegan(const vector<Touch*>& touches, Event *unused_event)
{
	std::vector<Touch*>::const_iterator touchIter = touches.begin();
	Touch* touch = (Touch*)(*touchIter);
	if (m_pJoystick->getBoundingBox().containsPoint(touch->getLocation()))
	{
		this->showJoystick();
		updateJoystick(touch);
		//CCLOG("***************");
		//CCLOG("update touch:%f %f", touch->getLocation().x, touch->getLocation().y);
		m_bisTouchDown = true;
		return;
	}
}

void Joystick::onTouchesMoved(const vector<Touch*>& touches, Event *unused_event)
{
	std::vector<Touch*>::const_iterator touchIter = touches.begin();
	Touch* touch = (Touch*)(*touchIter);
	if (m_pJoystick->isVisible())
	{
		updateJoystick(touch);
		return;
	}
}

void Joystick::onTouchesEnded(const vector<Touch*>& touches, Event *unused_event)
{
	//m_pJoystick->runAction(MoveTo::create(0.08f,start));
	//m_pJoystick->setPosition(start);
	//global->hero->onStop();
	if (m_bisTouchDown){
		g_GameManager->onPlayerStop();
		g_GameManager->onSPELayerStop();
		this->hideJoystick();
		m_bisTouchDown = false;
	}
}

void Joystick::onTouchesCancelled(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event)
{
	if (m_bisTouchDown)
	{
		//CCLOG("**********%s*****",__func__);
		m_bisTouchDown = false;
	}
}


void Joystick::setJoystick(Vec2 point)
{
	start = point;
	m_pJoystickBg->setPosition(start);
	m_pJoystick->setPosition(m_pJoystickBg->getPosition());
}
