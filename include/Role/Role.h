#ifndef _ROLE_H__
#define _ROLE_H__

#include "cocos2d.h"

namespace tds{

	class Role : public cocos2d::Sprite
	{
	protected:
		Role(std::string name = "");
		virtual ~Role();

	public:
		CC_SYNTHESIZE(std::string, m_Name, Name);

		CC_SYNTHESIZE(float , m_MaxHP,			MaxHP);
		CC_SYNTHESIZE(float , m_CurrentHP,		CurrentHP);
		CC_SYNTHESIZE(float , m_MoveSpeed,		MoveSpeed);

	};


};//end namespace tds

#endif
