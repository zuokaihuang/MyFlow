#ifndef _ROLE_H__
#define _ROLE_H__

#include "cocos2d.h"

namespace tds{

	enum class ActionState{
		ACTION_STATE_NONE = 0,
		ACTION_STATE_IDLE,
		ACTION_STATE_WALK,
		ACTION_STATE_L1,
		ACTION_STATE_L2,
		ACTION_STATE_L3,
		ACTION_STATE_L4,
	};

	class Role : public cocos2d::Sprite
	{
	protected:
		Role(std::string name = "");
		virtual ~Role();


	protected:
		static cocos2d::Animation* CreateNormalAnimation(const char* formatStr,
			unsigned int frameCount,
			int fps);


		static cocos2d::Animation* CreateAttackAnimation(const char* formatStr,
			int frameCountBegan,
			int frameCountEnd,
			int fps);

	public:
		CC_SYNTHESIZE(std::string, m_Name, Name);

		CC_SYNTHESIZE(ActionState, m_CurrentActionState, CurrentActionState);

		CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_pL1Action, L1Action);
		CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_pL2Action, L2Action);
		CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_pL3Action, L3Action);
		CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_pL4Action, L4Action);

		CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_pIdleAction, IdleAction);
		CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_pWalkAction, WalkAction);

		virtual void RunIdleAction();
		virtual void RunWalkAction();

		virtual void RunLevelAction(int level);	
		
		// the fllowing will read from server 
		//CC_SYNTHESIZE(float , m_MaxHP,			MaxHP);
		//CC_SYNTHESIZE(float , m_CurrentHP,		CurrentHP);
		CC_SYNTHESIZE(float ,	m_MaxMoveSpeed,	MaxMoveSpeed);
		CC_SYNTHESIZE(float , m_MoveSpeed,		MoveSpeed);
		CC_SYNTHESIZE(float , m_CurrentLevel,	CurrentLevel);

		CC_SYNTHESIZE(float , m_CurrentExperienceValue, CurrentExperienceValue);
		CC_SYNTHESIZE(float , m_ExperienceValueHold,	ExperienceValueHold);

		

	};


};//end namespace tds

#endif
