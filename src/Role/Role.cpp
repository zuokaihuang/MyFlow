
#include "Role.h"
#include "RoleEnergyPoints.h"
//#include "../../include/Role/Role.h"
using namespace tds;
USING_NS_CC;

Role::Role(std::string name)
:m_Name(name),
m_MaxHP(0),
m_CurrentHP(0),
m_MaxMoveSpeed(90),
m_MoveSpeed(30),
m_CurrentLevel(1),
m_LastVelocity(Vec2(-1,0)),
m_InWhichLayer(0),
m_CurrentExperienceValue(0),
m_ExperienceValueHold(0),
m_TurnCooldown(0),
m_pIdleAction(nullptr),
m_pWalkAction(nullptr),
m_pL1Action(nullptr),
m_pL2Action(nullptr),
m_pL3Action(nullptr),
m_pL4Action(nullptr),
m_CurrentActionState(ActionState::ACTION_STATE_L1)
{

}

Role::~Role()
{
	CC_SAFE_RELEASE_NULL(m_pIdleAction);
	CC_SAFE_RELEASE_NULL(m_pWalkAction);
	CC_SAFE_RELEASE_NULL(m_pL1Action);
	CC_SAFE_RELEASE_NULL(m_pL2Action);
	CC_SAFE_RELEASE_NULL(m_pL3Action);
	CC_SAFE_RELEASE_NULL(m_pL4Action);
	_kHPVector.clear();
}

Animation* Role::CreateAttackAnimation(const char* formatStr,
	int frameCountBegan,
	int frameCountEnd,
	int fps){

	//通过frameCountBegan,frameCountEnd从SpriteFrameCache中创建一个动作
	Vector<SpriteFrame*> pFrames;
	for (int i = frameCountBegan; i < frameCountEnd; i++)
	{
		const char* imgName = String::createWithFormat(formatStr, i)->getCString();
		SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
		pFrames.insert(i - frameCountBegan, pFrame);
	}
	return Animation::createWithSpriteFrames(pFrames, 1.0f / fps);

}

Animation* Role::CreateNormalAnimation(const char* formatStr,
	unsigned int frameCount,
	int fps){

	Vector<SpriteFrame*> pFrames;

	for (int i = 0; i < frameCount; i++)
	{
		const char* imgName = String::createWithFormat(formatStr, i)->getCString();
		SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
		pFrames.insert(i, pFrame);
	}
	return Animation::createWithSpriteFrames(pFrames, 1.0f / fps);
}
void Role::onUpdatePlayerExperienceValue(float value)
{
	this->m_CurrentExperienceValue += value;

}


void Role::RunIdleAction()
{

}

void Role::RunWalkAction()
{

}

void Role::RunLevelAction(int level)
{
	this->stopAllActions();

	Action* action = nullptr;
	switch (level)
	{
	case 1:
	{
		action = m_pL1Action;
		m_CurrentActionState = ActionState::ACTION_STATE_L1;
	}break;
	case 2:
	{
			  action = m_pL2Action;
			  m_CurrentActionState = ActionState::ACTION_STATE_L2;
			  
	}break;
	case 3:
	{
			  action = m_pL3Action;
			  m_CurrentActionState = ActionState::ACTION_STATE_L3;
	} break;
	case 4:
	{
			  action = m_pL4Action;
			  m_CurrentActionState = ActionState::ACTION_STATE_L4;
			 
	} break;
	default:
		break;
	}

	this->runAction(action);
}
void Role::addHP(tds::EnergyPoints* pHP)
{
	pHP->setWhoOwnerThisEnergyPonit(this);
	this->retain();
	_kHPVector.pushBack(pHP);
}

void Role::setVisible(bool visible)
{
	for (auto hp : _kHPVector)
		hp->setVisible(visible);
	Sprite::setVisible(visible);
}

void Role::setOpacity(GLubyte opacity)
{
	for (auto hp : _kHPVector)
		hp->setOpacity(opacity);
	Sprite::setOpacity(opacity);
}

void Role::removeFromParent()
{
	for (auto hp : _kHPVector)
		hp->removeFromParent();
	Sprite::removeFromParent();
}