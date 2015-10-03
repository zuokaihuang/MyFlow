
#include "Operate.h"
#include "GameManager.h"
#include "OperateLayer.h"

using namespace tds;
USING_NS_CC;

OperateLayer::OperateLayer()
{
	g_GameManager->m_OperateLayer = this;
	this->retain();
}

OperateLayer::~OperateLayer()
{
	//CC_SAFE_RELEASE(m_pBENPC);
}
 
bool OperateLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto pjoystick = Joystick::create();
		pjoystick->setJoystick(Vec2(origin.x + 100, origin.y+100));
		this->addChild(pjoystick);

		ret = true;
	} while (0);

	return ret;
}


